# CAPTURE DRIVER

## 1. Giới thiệu

File này mô tả driver Capture được viết cho vi điều khiển STM32F411CEU6.

Driver được xây dựng theo phương pháp Bare-metal, thao tác trực tiếp với các thanh ghi của vi điều khiển.

Các file liên quan:

- `capture.c`: Chứa phần hiện thực các hàm Capture.
- `capture.h`: Chứa khai báo hàm.
- `clock.h` : Cấp clock cho port sử dụng Capture và TIM5.

## 2. Phần cứng sử dụng

Vi điều khiển: `STM32F411CEU6`

Timer Peripheral: `TIM5`

Các chân GPIO: `PA0`

## 3. Cấu hình Capture

Driver cấu hình TIM5 hoạt động ở chế độ Input Capture.

Các thông số:

- Timer: `TIM5`
- Input Capture Channel 1: `TIM5_CH1`
- Input Capture Channel 2: `TIM5_CH2`
- Input: `TI1`
- GPIO: `PA0`
- Alternate Function: `AF2`
- Prescaler: `16 - 1`
- Auto Reload Register: `0xFFFFFFFF`
- Channel 1: `Rising Edge`
- Channel 2: `Falling Edge`

## 4. Các thanh ghi sử dụng

### GPIOA

- GPIOA_MODER
- GPIOA_AFRL

### TIM5

- TIM5_PSC
- TIM5_ARR
- TIM5_CCMR1
- TIM5_CCER
- TIM5_SMCR
- TIM5_CR1
- TIM5_CCR1
- TIM5_CCR2

## 5. Capture.h

- Khai báo các hàm sẽ được gọi trong thư viện khác :

    + `void capture_init()` : hàm cấu hình Input Capture

    + `uint32_t capture_frequency()` : Hàm đọc giá trị Capture dùng để xác định tần số

    + `uint32_t capture_pulse_width()` : Hàm đọc giá trị Capture dùng để xác định độ rộng xung

## 6. Capture.c

- Thực hiện các hàm Capture: 

* `capture_init()` : Hàm khởi tạo và cấu hình TIM5 Input Capture

    + Cấp clock cho GPIOA và TIM5

    + Cấu hình PA0 ở chế độ Alternate Function AF2

    + Cấu hình PA0 làm TIM5_CH1 Input Capture

    + Cấu hình TIM5_CH1 map với TI1

    + Cấu hình TIM5_CH2 map với TI1

    + Cấu hình Channel 1 Capture ở cạnh lên Rising Edge

    + Cấu hình Channel 2 Capture ở cạnh xuống Falling Edge

    + Cấu hình Prescaler = 16 - 1

    + Cấu hình Auto Reload Register = 0xFFFFFFFF

    + Cấu hình reset giá trị Counter khi có Rising Trigger Input

    + Enable Counter TIM5

    + Không nhận tham số đầu vào

    + Không có giá trị trả về

    + `Ví dụ` : `capture_init()`

* `capture_frequency()` : Hàm đọc giá trị Capture trong thanh ghi TIM5_CCR1 dùng để xác định tần số tín hiệu

    + Không nhận tham số đầu vào

    + `Ví dụ` : `capture_frequency()`

* `capture_pulse_width()` : Hàm đọc giá trị Capture trong thanh ghi TIM5_CCR2 dùng để xác định độ rộng xung

    + Không nhận tham số đầu vào

    + `Ví dụ` : `capture_pulse_width()`
