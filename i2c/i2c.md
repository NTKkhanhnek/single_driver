# I2C DRIVER

## 1. Giới thiệu

File này mô tả driver I2C được viết cho vi điều khiển STM32F411CEU6.

Driver được xây dựng theo phương pháp Bare-metal, thao tác trực tiếp với các thanh ghi của vi điều khiển.

Các file liên quan:

- 'i2c.c': Chứa phần hiện thực các hàm I2C.
- 'i2c.h': Chứa khai báo hàm, kiểu dữ liệu và các định nghĩa cần thiết.


## 2. Phần cứng sử dụng

Vi điều khiển:

STM32F411CEU6

I2C Peripheral:

I2C1

Các chân GPIO:

| Chức năng | Chân STM32 | Alternate Function |
|-----------|------------|--------------------|
| SCL       | PB8        | AF4                |
| SDA       | PB9        | AF4                |

---

## 3. Cấu hình I2C

Driver cấu hình I2C1 hoạt động ở chế độ Master.

Các thông số:

- Clock I2C: ...
- Tốc độ I2C: 100 kHz / 400 kHz
- Chế độ địa chỉ: 7-bit
- SCL: PB8
- SDA: PB9

---

## 4. Các thanh ghi sử dụng

### RCC

Dùng để cấp clock cho GPIOB và I2C1.

Các thanh ghi liên quan:

- RCC_AHB1ENR
- RCC_APB1ENR

### GPIOB

Dùng để cấu hình PB8 và PB9 thành Alternate Function AF4.

Các thanh ghi liên quan:

- GPIOB_MODER
- GPIOB_OTYPER
- GPIOB_OSPEEDR
- GPIOB_PUPDR
- GPIOB_AFRH

### I2C1

Các thanh ghi chính:

- I2C_CR1
- I2C_CR2
- I2C_DR
- I2C_SR1
- I2C_SR2
- I2C_CCR
- I2C_TRISE

---

## 5. Các hàm trong driver

### `I2C_init()`

```c
void I2C_init(void);