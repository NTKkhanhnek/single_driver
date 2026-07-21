# PWM DRIVER

## 1. Giới thiệu

File này mô tả driver PWM được viết cho vi điều khiển STM32F411CEU6.

Driver được xây dựng theo phương pháp Bare-metal, thao tác trực tiếp với các thanh ghi của vi điều khiển.

Các file liên quan:

- `pwm.c`: Chứa phần hiện thực các hàm PWM.
- `pwm.h`: Chứa khai báo hàm.
- `clock.h` : Cấp clock cho GPIOB và TIM4 sử dụng PWM.

## 2. Phần cứng sử dụng

Vi điều khiển: `STM32F411CEU6`

Timer Peripheral: `TIM4`

Các chân GPIO: `PB6`  `PB7`  `PB8`  `PB9`

## 3. Cấu hình PWM

Driver cấu hình TIM4 hoạt động ở chế độ PWM Output.

Các thông số:

- Timer: `TIM4`
- Channel 1: `TIM4_CH1` - `PB6`
- Channel 2: `TIM4_CH2` - `PB7`
- Channel 3: `TIM4_CH3` - `PB8`
- Channel 4: `TIM4_CH4` - `PB9`
- Alternate Function: `AF2`
- Prescaler: `16 - 1`
- Auto Reload Register: `20000`
- PWM Mode: `PWM Mode 1`
- Pulse Width Minimum: `1100`
- Pulse Width Maximum: `1950`

## 4. Các thanh ghi sử dụng

### GPIOB

- GPIOB_MODER
- GPIOB_AFRL
- GPIOB_AFRH

### TIM4

- TIM4_PSC
- TIM4_ARR
- TIM4_CCR1
- TIM4_CCR2
- TIM4_CCR3
- TIM4_CCR4
- TIM4_CCMR1
- TIM4_CCMR2
- TIM4_CCER
- TIM4_CR1

## 5. PWM.h

- Khai báo các hàm sẽ được gọi trong thư viện khác :

    + `void pwm_init()` : hàm cấu hình PWM

    + `void control_motor(uint8_t motor, uint16_t pulse_width)` : Hàm điều khiển độ rộng xung PWM cho Motor

## 6. PWM.c

- Thực hiện các hàm PWM: 

* `pwm_init()` : Hàm khởi tạo và cấu hình TIM4 PWM

    + Cấp clock cho GPIOB và TIM4

    + Cấu hình PB6, PB7, PB8, PB9 ở chế độ Alternate Function AF2

    + Cấu hình PB6 làm TIM4_CH1

    + Cấu hình PB7 làm TIM4_CH2

    + Cấu hình PB8 làm TIM4_CH3

    + Cấu hình PB9 làm TIM4_CH4

    + Cấu hình Prescaler = 16 - 1

    + Cấu hình Auto Reload Register = 20000

    + Cấu hình Channel 1, 2, 3, 4 hoạt động ở PWM Mode 1

    + Enable Output cho Channel 1, 2, 3, 4

    + Enable Counter TIM4

    + Không nhận tham số đầu vào

    + Không có giá trị trả về

    + `Ví dụ` : `pwm_init()`

* `control_motor(uint8_t motor, uint16_t pulse_width)` : Hàm điều khiển độ rộng xung PWM của Motor

    + `motor` : Motor cần điều khiển từ 1 đến 4

    + `pulse_width` : độ rộng xung PWM, giới hạn từ 1100 đến 1950

    + `Ví dụ` : `control_motor(1, 1500)` điều khiển Motor 1 với Pulse Width = 1500
