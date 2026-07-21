# DELAY DRIVER

## 1. Giới thiệu

File này mô tả driver Delay được viết cho vi điều khiển STM32F411CEU6.

Driver được xây dựng theo phương pháp Bare-metal, thao tác trực tiếp với các thanh ghi của vi điều khiển.

Các file liên quan:

- `delay.c`: Chứa phần hiện thực các hàm Delay.
- `delay.h`: Chứa khai báo hàm.
- `clock.h` : Cấp clock cho Timer sử dụng Delay.

## 2. Phần cứng sử dụng

Vi điều khiển: `STM32F411CEU6`

Delay Source: `TIM1` hoặc `SysTick`

Nguồn đang sử dụng: `TIM1`

## 3. Cấu hình Delay

Driver cấu hình Delay sử dụng TIM1 hoặc SysTick.

Các thông số:

- Delay Source: `TIM1`
- Timer Peripheral: `TIM1`
- Prescaler: `16 - 1`
- Auto Reload Register: `1000`
- TIM1 Interrupt: `Enable`
- NVIC TIM1 Interrupt: `Enable`

## 4. Các thanh ghi sử dụng

### TIM1

- TIM1_PSC
- TIM1_ARR
- TIM1_DIER
- TIM1_CR1
- TIM1_SR

### NVIC

- NVIC_ISER0

### SysTick

- SYST_CSR
- SYST_RVR

## 5. Delay.h

- Khai báo các hàm sẽ được gọi trong thư viện khác :

    + `void delay_init()` : hàm cấu hình Delay

    + `void delay_ms(uint32_t ms)` : Hàm tạo thời gian Delay theo đơn vị millisecond

## 6. Delay.c

- Thực hiện các hàm Delay: 

* `delay_init(void)` : Hàm khởi tạo và cấu hình nguồn Delay

    + Nếu sử dụng TIM1 thì cấp clock cho TIM1

    + Cấu hình Prescaler = 16 - 1

    + Cấu hình Auto Reload Register = 1000

    + Enable Interrupt cho TIM1

    + Enable Counter TIM1

    + Enable TIM1 Interrupt trong NVIC

    + Nếu sử dụng SysTick thì Enable SysTick và SysTick Interrupt

    + Cấu hình SYST_RVR = 16000 - 1

    + Không nhận tham số đầu vào

    + Không có giá trị trả về

    + `Ví dụ` : `delay_init()`

* `TIM1_UP_TIM10_IRQHandler()` : Hàm xử lý ngắt TIM1 khi Timer Update Event xảy ra

    + Xóa cờ UIF

    + Tăng biến `tim1_cnt` lên 1

* `delay_ms(uint32_t ms)` : Hàm tạo thời gian Delay theo giá trị millisecond truyền vào

    + `ms` : thời gian Delay theo đơn vị millisecond

    + `Ví dụ` : `delay_ms(1000)` tạo Delay 1000ms
