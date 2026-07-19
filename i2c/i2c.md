# I2C DRIVER

## 1. Giới thiệu

File này mô tả driver I2C được viết cho vi điều khiển STM32F411CEU6.

Driver được xây dựng theo phương pháp Bare-metal, thao tác trực tiếp với các thanh ghi của vi điều khiển.

Các file liên quan:

- `i2c.c`: Chứa phần hiện thực các hàm I2C.
- `i2c.h`: Chứa khai báo hàm, kiểu dữ liệu và các định nghĩa cần thiết.
- `clock.h` : Cấp clock cho port sử dụng i2c và i2c

## 2. Phần cứng sử dụng

Vi điều khiển: STM32F411CEU6

I2C Peripheral: I2C1

Các chân GPIO:

| Chức năng | Chân STM32 | Alternate Function |
|-----------|------------|--------------------|
| SCL       | PB6        | AF4                |
| SDA       | PB7        | AF4                |

## 3. Cấu hình I2C

Driver cấu hình I2C1 hoạt động ở chế độ Master.

Các thông số:

- Clock I2C: 50MHz (PCLK1)
- Tốc độ I2C: 100kHz (STANDARD MODE)
- Chế độ địa chỉ: 7-bit
- SCL: PB6
- SDA: PB7

## 4. Các thanh ghi sử dụng

### GPIOB

Dùng để cấu hình PB6 và PB7 thành Alternate Function AF4.

Các thanh ghi liên quan:

- GPIOB_MODER
- GPIOB_OTYPER
- GPIOB_OSPEEDR
- GPIOB_PUPDR
- GPIOB_AFRL

### I2C1

Các thanh ghi chính:

- I2C_CR1
- I2C_CR2
- I2C_OAR1
- I2C_DR
- I2C_SR1
- I2C_SR2
- I2C_CCR
- I2C_TRISE

## 5. i2c.h

- Tạo kiểu dữ liệu trả về trạng thái `I2C_Status_t`

- Khai báo các hàm sẽ được gọi trong thư viện khác :

    + void i2c_init(void) : hàm cấu hình

    + I2C_Status_t i2c_mem_write(uint8_t dev_addr, uint8_t mem_addr, const uint8_t *data, uint16_t len) : hàm ghi data vào thanh ghi của cảm biến

    + I2C_Status_t i2c_mem_read(uint8_t dev_addr, uint8_t mem_addr, uint8_t *data, uint16_t len) : hàm đọc data từ thanh ghi của cảm biến

## 6. i2c.c
