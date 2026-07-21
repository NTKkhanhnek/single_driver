# EXTI0 DRIVER

## 1. Giới thiệu

File này mô tả driver EXTI0 được viết cho vi điều khiển STM32F411CEU6.

Driver được xây dựng theo phương pháp Bare-metal, thao tác trực tiếp với các thanh ghi của vi điều khiển.

Các file liên quan:

- `exti0.c`: Chứa phần hiện thực các hàm EXTI0.
- `exti0.h`: Chứa khai báo hàm.
- `clock.h` : Cấp clock cho GPIOA sử dụng EXTI0.

## 2. Phần cứng sử dụng

Vi điều khiển: `STM32F411CEU6`

GPIO Port: `GPIOA`

External Interrupt Line: `EXTI0`

NVIC Interrupt Position: `6`

## 3. Cấu hình EXTI0

Driver cấu hình EXTI0 hoạt động ở chế độ External Interrupt.

Các thông số:

- EXTI Line: `EXTI0`
- Trigger: `Rising Edge`
- Interrupt Mask: `Enable`
- NVIC Interrupt: `Enable`
- NVIC ISER0 Bit: `6`

## 4. Các thanh ghi sử dụng

### EXTI

- EXTI_IMR
- EXTI_RTSR
- EXTI_PR

### NVIC

- NVIC_ISER0

## 5. EXTI0.h

- Khai báo các hàm sẽ được gọi trong thư viện khác :

    + `void exti0_handler()` : Hàm xử lý ngắt EXTI0

    + `void exti0_init()` : hàm cấu hình EXTI0

## 6. EXTI0.c

- Thực hiện các hàm EXTI0: 

* `exti0_init()` : Hàm khởi tạo và cấu hình EXTI0

    + Cấp clock cho GPIOA

    + Cấu hình EXTI0 Trigger ở cạnh lên Rising Edge

    + Enable EXTI0 trong Interrupt Mask Register

    + Enable EXTI0 Interrupt trong NVIC ISER0 bit 6

    + Không nhận tham số đầu vào

    + Không có giá trị trả về

    + `Ví dụ` : `exti0_init()`

* `exti0_handler()` : Hàm xử lý ngắt EXTI0

    + Xóa cờ Pending của EXTI0 sau khi ngắt xảy ra

    + Không nhận tham số đầu vào

    + Không có giá trị trả về

    + `Ví dụ` : `exti0_handler()`
