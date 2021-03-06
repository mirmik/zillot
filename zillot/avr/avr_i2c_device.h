#ifndef ZILLOT_AVR_ARCH_I2C_H
#define ZILLOT_AVR_ARCH_I2C_H

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>

#include <igris/dprint.h>
#include <igris/util/bug.h>

#include <zillot/i2c/i2c_device.h>

// 0x00 Bus Fail Автобус сломался… эээ в смысле аппаратная ошибка шины.
// Например, внезапный старт посреди передачи бита. 0x08 Start Был сделан старт.
// Теперь мы решаем что делать дальше, например послать адрес ведомого 0x10
// ReStart Был обнаружен повторный старт. Можно переключиться с записи на чтение
// или наоборот. От логики зависит. 0x18 SLA+W+ACK Мы отправили адрес с битом
// записи, а в ответ получили ACK от ведомого. Значит можно продолжать. 0x20
// SLA+W+NACK Мы отправили адрес с битом записи, а нас послали NACK. Обидно,
// сгенерим ошибку или повторим еще раз. 0x28 Byte+ACK Мы послали байт и получили
// подтверждение, что ведомый его принял. Продолжаем. 0x30 Byte+NACK Мы послали
// байт, но подтверждение не получили. Видимо ведомый уже сыт по горло нашими
// подачками или он захлебнулся в данных. Либо его ВНЕЗАПНО посреди передачи
// данных украли инопланетяне. 0x38 Collision А у нас тут клановые разборки —
// пришел другой мастер, по хамски нас перебил, да так, что мы от возмущения аж
// заткнулись. Ничего I’l be back! До встречи через n тактов! 0x40 SLA+R+ACK
// Послали адрес с битом на чтение, а ведомый отозвался. Хорошо! Будем читать.
// 0x48 SLA+R+NACK Крикнули в шину «Эй ты, с адресом ХХХ, почитай нам сказки» А
// в ответ «Иди NACK!» В смысле на запрос адреса с битом чтения никто не
// откликнулся. Видимо не хотят или заняты. Также может быть никого нет дома.
// 0x50 Receive Byte Мы приняли байт. И думаем что бы ответить ведомому. ACK или
// NACK. 0x58 Receive Byte+NACK Мы приняли байт от ведомого и сказали ему «иди
// NACK!» И он обиженый ушел, освободив шину.

// 0x68 Receive SLA+W LP Мы были мастером, трепались с подчиненными по шине. И
// тут появляется на шине другой, более равный, мастер, перебивает нас и молвит
// «Уважаемый ХХ, а не возьмете ли вы вот эти байтики…» Чтож, он круче. Придется
// бросать передачу и брать его байты себе. 0x78 Receive SLA+W LP Broadcast Были
// мы, как нам казалось, самыми крутыми мастерами на шине. Пока не появился
// другой мастер и перебив нас прогундосил на всю шину «Эй, слышь тыыы. Слушай
// сюда» Девайсы-лохи, с неотключенными широковещательными запросами подчиняются.
// Остальные отмораживаются и всякое Broadcast-быдло игнорируют. 0x60 Receive
// SLA+W Сидим на шине, никого не трогаем, ни с кем не общаемся. А тут нас по
// имени… Конечно отзовемся :) 0x70 Receive SLA+W Broadcast Ситуация повторяется,
// но на этот раз слышим уже знакомое нам «Слышь, тыыыы». Кто? К кому? Игнорируем
// Broadcast запросы? Или нет? Зависит от моральных качеств программы. 0x80
// Receive Byte & 0x90 Receive Byte Broadcast Принимаем байты. От кого и в каком
// виде не важно. Решаем что сказать Давай еще (ACK) или «Иди NACK». Тут уже по
// обстоятельствам. 0x88 Receive Last Byte & 0x98 Receive Last Byte Broadcast
// Приняли последний байт и распихиваем по карманам. 0xA0 Receive ReStart Ой у
// нас Повторный старт. Видимо то что пришло в первый раз был таки адрес
// страницы. А сейчас пойдут данные… 0xB0 Receive SLA+R LP Слали мы что то слали,
// а тут нас перебивает другой мастер, обращается по имени и говорит «А ну ХХ
// зачитай нам что нибудь из Пушкина» Что делать, приходится читать. 0xA8 Receive
// SLA+R Либо просто к нам какой то другой мастер по имени обращается и просить
// ему передать байтиков. 0xB8 Send Byte Receive ACK Ну дали мы ему байт. Он нам
// ACK. А мы тем временем думаем слать ему еще один (последний) и говорить «иди
// NACK». Или же у нас дофига их и можно еще пообщаться. 0xC0 Send Last Byte
// Receive NACK Дали мастеру последний имеющийся байт, а он нам «иди NACK».
// Хамло. Ну и хрен с ним. Уходим с шины. 0xC8 Send Last Byte Receive ACK Дали
// мастеру последний имеющийся байт, а он требует еще. Но у нас нету, так что
// разворачиваемся и уходим с шины. А он пусть карманы воздухом наполняет (в этот
// момент мастер начнет получать якобы от slave 0xFF байты, на самом деле это
// просто чтение висящей шины).

enum AvrI2CType
{
    I2C_SAWP = 0x00,
    I2C_SARP = 0x01,
    I2C_SAWSARP = 0x02,
};

struct avr_i2c_device
{
    struct i2c_bus_device dev;
    sem_t internal_lock;

    uint8_t target_address;
    const void *sendbuf;
    int sendlen;
    void *recvbuf;
    int recvlen;
    int it;
    int rbytecount;

    union u_s
    {
        uint8_t flags;
        struct f_s
        {
            uint8_t type : 2;
            uint8_t ERR_BF : 1;
            uint8_t ERR_NA : 1;
            uint8_t ERR_NK : 1;
        } f;
    } u;
};

extern const struct i2c_bus_device_operations avr_i2c_device_operations;

__BEGIN_DECLS

void avr_i2c_irq_handler(void *);
void avr_i2c_device_init_master(struct avr_i2c_device *i2c,
                                uint32_t scl_freq_hz);
void avr_i2c_device_enable();

__END_DECLS

#define DECLARE_AVR_I2C_WITH_IRQS(name)                                        \
    struct avr_i2c_device name = {                                             \
        .dev = I2C_INIT(name.dev, &avr_i2c_device_operations),                 \
        .internal_lock = SEMAPHORE_INIT(name.internal_lock, 0),                \
        .target_address = 0,                                                   \
        .sendbuf = 0,                                                          \
        .sendlen = 0,                                                          \
        .recvbuf = 0,                                                          \
        .recvlen = 0,                                                          \
        .it = 0,                                                               \
        .rbytecount = 0,                                                       \
        .u = {.flags = 0}};                                                    \
    ISR(TWI_vect) { avr_i2c_irq_handler(&name); }

#endif