# CLOCK DRIVER

## 1. Giới thiệu

File này mô tả driver Clock được viết cho vi điều khiển STM32F411CEU6.

Driver được xây dựng theo phương pháp Bare-metal, thao tác trực tiếp với các thanh ghi của vi điều khiển.

Các file liên quan:

- `clock.c`: Chứa phần hiện thực các hàm Clock.
- `clock.h`: Chứa khai báo hàm, kiểu dữ liệu và các định nghĩa cần thiết.

## 2. Phần cứng sử dụng

Vi điều khiển: `STM32F411CEU6`

Clock Source: `HSE 25MHz`

System Clock: `100MHz`

## 3. Cấu hình Clock

Driver cấu hình System Clock sử dụng HSE và PLL.

Các thông số:

- HSE: `25MHz`
- PLLM: `25`
- PLLN: `200`
- PLLP: `2`
- SYSCLK: `100MHz`
- AHB Clock: `100MHz`
- APB1 Clock: `50MHz`
- APB2 Clock: `100MHz`
- Flash Latency: `3 WS`

## 4. Các thanh ghi sử dụng

### RCC

- RCC_CR
- RCC_PLLCFGR
- RCC_CFGR
- RCC_AHB1ENR
- RCC_AHB2ENR
- RCC_APB1ENR
- RCC_APB2ENR

### FLASH

- FLASH_ACR

## 5. Clock.h

- Định nghĩa System Clock `RCC_SYS_CLOCK_HZ = 100000000`

- Định nghĩa APB1 Clock `RCC_APB1_CLOCK_HZ = 50000000`

- Tạo kiểu dữ liệu Peripheral AHB1 `AHB1_peripheral_t`

- Tạo kiểu dữ liệu Peripheral AHB2 `AHB2_peripheral_t`

- Tạo kiểu dữ liệu Peripheral APB1 `APB1_peripheral_t`

- Tạo kiểu dữ liệu Peripheral APB2 `APB2_peripheral_t`

- Khai báo các hàm sẽ được gọi trong thư viện khác :

    + `void clock_enable_AHB1(AHB1_peripheral_t peripheral)` : Hàm cấp clock cho Peripheral trên bus AHB1

    + `void clock_enable_AHB2(AHB2_peripheral_t peripheral)` : Hàm cấp clock cho Peripheral trên bus AHB2

    + `void clock_enable_APB1(APB1_peripheral_t peripheral)` : Hàm cấp clock cho Peripheral trên bus APB1

    + `void clock_enable_APB2(APB2_peripheral_t peripheral)` : Hàm cấp clock cho Peripheral trên bus APB2

    + `void clock_init(void)` : hàm cấu hình Clock

## 6. Clock.c

- Thực hiện các hàm Clock: 

* `clock_init(void)` : Hàm khởi tạo và cấu hình System Clock

    + Bật HSE 25MHz

    + Chờ HSE sẵn sàng

    + Cấu hình Flash Latency = 3 WS

    + Cấu hình PLLM = 25

    + Cấu hình PLLN = 200

    + Cấu hình PLLP = 2

    + Chọn HSE làm nguồn vào cho PLL

    + Bật PLL và chờ PLL sẵn sàng

    + Cấu hình AHB không chia

    + Cấu hình APB1 chia 2

    + Cấu hình APB2 không chia

    + Chọn PLL làm System Clock

    + Không nhận tham số đầu vào

    + Không có giá trị trả về

    + `Ví dụ` : `clock_init()`

* `clock_enable_AHB1(AHB1_peripheral_t peripheral)` : Hàm cấp clock cho một Peripheral trên bus AHB1

    + `peripheral` : Peripheral trên bus AHB1 cần cấp clock

    + `Ví dụ` : `clock_enable_AHB1(GPIOA_peripheral)`

* `clock_enable_AHB2(AHB2_peripheral_t peripheral)` : Hàm cấp clock cho một Peripheral trên bus AHB2

    + `peripheral` : Peripheral trên bus AHB2 cần cấp clock

    + `Ví dụ` : `clock_enable_AHB2(OTGFS_peripheral)`

* `clock_enable_APB1(APB1_peripheral_t peripheral)` : Hàm cấp clock cho một Peripheral trên bus APB1

    + `peripheral` : Peripheral trên bus APB1 cần cấp clock

    + `Ví dụ` : `clock_enable_APB1(I2C1_peripheral)`

* `clock_enable_APB2(APB2_peripheral_t peripheral)` : Hàm cấp clock cho một Peripheral trên bus APB2

    + `peripheral` : Peripheral trên bus APB2 cần cấp clock

    + `Ví dụ` : `clock_enable_APB2(SPI1_peripheral)`
