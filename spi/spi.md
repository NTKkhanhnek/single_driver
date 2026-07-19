# SPI DRIVER

## 1. Giới thiệu

File này mô tả driver SPI được viết cho vi điều khiển STM32F411CEU6.

Driver được xây dựng theo phương pháp Bare-metal, thao tác trực tiếp với các thanh ghi của vi điều khiển.

Các file liên quan:

- `spi.c`: Chứa phần hiện thực các hàm SPI.
- `spi.h`: Chứa khai báo hàm, kiểu dữ liệu và các định nghĩa cần thiết.
- `clock.h` : Cấp clock cho port sử dụng SPI và SPI.

## 2. Phần cứng sử dụng

Vi điều khiển: `STM32F411CEU6`

SPI Peripheral: `SPI1`

Các chân GPIO: `PA4`  `PA5`  `PA6`  `PA7`

## 3. Cấu hình SPI

Driver cấu hình SPI1 hoạt động ở chế độ Master.

Các thông số:

- Clock SPI: `100MHz` (PCLK2)
- Tốc độ SPI: `12.5MHz`
- Chế độ SPI: `MODE 0` (CPOL = 0, CPHA = 0)
- Khung dữ liệu: `8-bit`
- Thứ tự bit: `MSB First`
- Chế độ truyền: `Full-Duplex`
- CS: `PA4`
- SCK: `PA5`
- MISO: `PA6`
- MOSI: `PA7`

## 4. Các thanh ghi sử dụng

### GPIOA

- GPIOA_MODER
- GPIOA_OTYPER
- GPIOA_OSPEEDR
- GPIOA_PUPDR
- GPIOA_BSRR
- GPIOA_AFRL

### SPI1

- SPI1_CR1
- SPI1_CR2
- SPI1_SR
- SPI1_DR
- SPI1_CRCPR
- SPI1_RXCRCR
- SPI1_TXCRCR

## 5. SPI.h

- Tạo kiểu dữ liệu trả về trạng thái `SPI_Status_t`

- Tạo kiểu dữ liệu trạng thái chân CS `SPI_CS_State_t`

- Khai báo các hàm sẽ được gọi trong thư viện khác :

    + `void SPI_init(void)` : hàm cấu hình SPI

    + `SPI_Status_t SPI_mem_write(uint8_t reg_addr, const uint8_t *data, uint16_t len)` : Hàm ghi dữ liệu vào một thanh ghi cụ thể của Slave

    + `SPI_Status_t SPI_mem_read(uint8_t reg_addr, uint8_t *data, uint16_t len)` : Hàm đọc dữ liệu từ một thanh ghi cụ thể của Slave

## 6. SPI.c

- Thực hiện các hàm SPI: 

* `spi_wait_flag_set(volatile uint32_t *reg, uint32_t flag)` : Hàm chờ cờ trạng thái được set lên 1

    + `reg` : địa chỉ thanh ghi chứa bit cờ 

    + `flag`: vị trí bit cờ 

    + `Ví dụ`: `spi_wait_flag_set(SPI1_SR, SPI_SR_TXE)`

* `spi_wait_flag_reset(volatile uint32_t *reg, uint32_t flag)` : Hàm chờ cờ trạng thái được reset về 0

    + `reg` : địa chỉ thanh ghi chứa bit cờ

    + `flag` : vị trí bit cờ

    + `Ví dụ` : `spi_wait_flag_reset(SPI1_SR, SPI_SR_BSY)`

* `spi_clear_ovr_flag(void)` : Hàm xóa cờ `OVR` bằng cách đọc lần lượt thanh ghi `SPI1_DR` và `SPI1_SR`

* `SPI_cs_low(void)` : Hàm kéo chân CS xuống mức thấp để bắt đầu giao tiếp với Slave

* `SPI_cs_high(void)` : Hàm kéo chân CS lên mức cao để kết thúc giao tiếp với Slave

* `SPI_init(void)` : Hàm khởi tạo và cấu hình SPI1

    + Cấp clock cho GPIOA và SPI1

    + Cấu hình PA4 làm CS, PA5 làm SCK, PA6 làm MISO và PA7 làm MOSI

    + Cấu hình PA5, PA6 và PA7 ở chế độ Alternate Function AF5

    + Cấu hình chân ở chế độ Push-pull

    + Cấu hình Pull-up cho CS

    + Cấu hình PCLK2 = 100 MHz

    + Cấu hình Baud Rate Prescaler = 8

    + Cấu hình SPI hoạt động với tốc độ 12.5 MHz

    + Cấu hình SPI ở Mode 0 với CPOL = 0 và CPHA = 0

    + Cấu hình khung dữ liệu 8-bit

    + Cấu hình truyền MSB First

    + Cấu hình SPI hoạt động ở chế độ Full-Duplex

    + Không nhận tham số đầu vào

    + Không có giá trị trả về

    + `Ví dụ` : `SPI_init()`

* `SPI_transfer_byte(uint8_t tx_data, uint8_t *rx_data)` : Hàm gửi và nhận đồng thời một byte dữ liệu qua SPI

    + `tx_data` : byte dữ liệu cần gửi

    + `rx_data` : địa chỉ biến dùng để lưu byte dữ liệu nhận được

    + `Ví dụ` : `SPI_transfer_byte(0xFF, &data)`

* `SPI_transmit(const uint8_t *data, uint16_t len)` : Hàm gửi một hoặc nhiều byte dữ liệu qua SPI

    + `data` : địa chỉ vùng dữ liệu cần gửi

    + `len` : số byte dữ liệu cần gửi

    + `Ví dụ` : `SPI_transmit(data, 3)` gửi 3 byte dữ liệu

* `SPI_receive(uint8_t *data, uint16_t len)` : Hàm nhận một hoặc nhiều byte dữ liệu qua SPI

    + `data` : địa chỉ vùng nhớ dùng để lưu dữ liệu nhận được

    + `len` : số byte dữ liệu cần nhận

    + `Ví dụ` : `SPI_receive(data, 6)` nhận 6 byte dữ liệu

* `SPI_transmit_receive(const uint8_t *tx_data, uint8_t *rx_data, uint16_t len)` : Hàm gửi và nhận đồng thời một hoặc nhiều byte dữ liệu qua SPI

    + `tx_data` : địa chỉ vùng dữ liệu cần gửi

    + `rx_data` : địa chỉ vùng nhớ dùng để lưu dữ liệu nhận được

    + `len` : số byte dữ liệu cần gửi và nhận

    + `Ví dụ` : `SPI_transmit_receive(tx_data, rx_data, 3)` gửi và nhận đồng thời 3 byte dữ liệu

* `SPI_mem_write(uint8_t reg_addr, const uint8_t *data, uint16_t len)` : Hàm ghi dữ liệu vào một thanh ghi cụ thể của Slave

    + `reg_addr` : địa chỉ thanh ghi bên trong Slave cần ghi dữ liệu

    + `data` : địa chỉ vùng dữ liệu cần ghi

    + `len` : số byte dữ liệu cần ghi

    + `Ví dụ` : `SPI_mem_write(0x10, &data, 1)` ghi 1 byte dữ liệu vào thanh ghi `0x10` của Slave

* `SPI_mem_read(uint8_t reg_addr, uint8_t *data, uint16_t len)` : Hàm đọc dữ liệu từ một thanh ghi cụ thể của Slave

    + `reg_addr` : địa chỉ thanh ghi bên trong Slave cần đọc dữ liệu

    + `data` : địa chỉ vùng nhớ dùng để lưu dữ liệu đọc được

    + `len` : số byte dữ liệu cần đọc

    + `Ví dụ` : `SPI_mem_read(0x75, &data, 1)` đọc 1 byte từ thanh ghi `0x75` của Slave
