# UART2 DRIVER

## 1. Giới thiệu

File này mô tả driver UART2 được viết cho vi điều khiển STM32F411CEU6.

Driver được xây dựng theo phương pháp Bare-metal, thao tác trực tiếp với các thanh ghi của vi điều khiển.

Các file liên quan:

- `uart2.c`: Chứa phần hiện thực các hàm UART2.
- `uart2.h`: Chứa khai báo hàm và các định nghĩa cần thiết.
- `clock.h` : Cấp clock cho port sử dụng UART2 và USART2.

## 2. Phần cứng sử dụng

Vi điều khiển: `STM32F411CEU6`

UART Peripheral: `USART2`

Các chân GPIO: `PA2`  `PA3`

## 3. Cấu hình UART2

Driver cấu hình USART2 hoạt động ở chế độ truyền và nhận dữ liệu.

Các thông số:

- Clock UART2: `50MHz` (PCLK1)
- Baudrate: `115200`
- Khung dữ liệu: `8-bit`
- Parity: `None`
- Stop bit: `1`
- TX: `PA2`
- RX: `PA3`

## 4. Các thanh ghi sử dụng

### GPIOA

- GPIOA_MODER
- GPIOA_OTYPER
- GPIOA_OSPEEDR
- GPIOA_PUPDR
- GPIOA_AFRL

### USART2

- USART2_SR
- USART2_DR
- USART2_BRR
- USART2_CR1
- USART2_CR2
- USART2_CR3

## 5. UART2.h

- Định nghĩa Baudrate UART2 là `115200`

- Khai báo các hàm sẽ được gọi trong thư viện khác :

    + `void uart2_init(void)` : hàm cấu hình UART2

    + `void uart2_send_char(char data)` : Hàm gửi một ký tự qua UART2

    + `void uart2_send_string(const char *str)` : Hàm gửi một chuỗi ký tự qua UART2

    + `void uart2_send_uint(uint32_t value)` : Hàm gửi một số nguyên không dấu qua UART2

    + `void uart2_send_int(int32_t value)` : Hàm gửi một số nguyên có dấu qua UART2

    + `void uart2_send_float(float value, uint8_t decimal)` : Hàm gửi một số thực qua UART2

## 6. UART2.c

- Thực hiện các hàm UART2: 

* `uart2_calculate_brr(uint32_t pclk, uint32_t baudrate)` : Hàm tính giá trị thanh ghi BRR dựa trên clock PCLK và Baudrate

    + `pclk` : tần số clock cấp cho USART2

    + `baudrate` : tốc độ Baudrate cần cấu hình

    + `Ví dụ` : `uart2_calculate_brr(RCC_APB1_CLOCK_HZ, UART2_BAUDRATE)`

* `uart2_init(void)` : Hàm khởi tạo và cấu hình USART2

    + Cấp clock cho GPIOA và USART2

    + Cấu hình PA2 làm TX và PA3 làm RX

    + Cấu hình PA2 và PA3 ở chế độ Alternate Function AF7

    + Cấu hình chân ở chế độ Push-pull

    + Cấu hình Pull-up cho TX và RX

    + Cấu hình PCLK1 = 50 MHz

    + Cấu hình Baudrate = 115200

    + Cho phép USART2 truyền dữ liệu

    + Cho phép USART2 nhận dữ liệu

    + Không nhận tham số đầu vào

    + Không có giá trị trả về

    + `Ví dụ` : `uart2_init()`

* `uart2_send_char(char data)` : Hàm gửi một ký tự qua UART2

    + `data` : ký tự cần gửi

    + `Ví dụ` : `uart2_send_char('A')` gửi ký tự `A`

* `uart2_send_string(const char *str)` : Hàm gửi một chuỗi ký tự qua UART2

    + `str` : địa chỉ chuỗi ký tự cần gửi

    + `Ví dụ` : `uart2_send_string("Hello")` gửi chuỗi ký tự `Hello`

* `uart2_send_uint(uint32_t value)` : Hàm gửi một số nguyên không dấu qua UART2

    + `value` : giá trị số nguyên không dấu cần gửi

    + `Ví dụ` : `uart2_send_uint(123)` gửi số `123`

* `uart2_send_int(int32_t value)` : Hàm gửi một số nguyên có dấu qua UART2

    + `value` : giá trị số nguyên có dấu cần gửi

    + `Ví dụ` : `uart2_send_int(-123)` gửi số `-123`

* `uart2_send_float(float value, uint8_t decimal)` : Hàm gửi một số thực qua UART2

    + `value` : giá trị số thực cần gửi

    + `decimal` : số chữ số sau dấu thập phân cần gửi

    + `Ví dụ` : `uart2_send_float(12.34, 2)` gửi số `12.34`
