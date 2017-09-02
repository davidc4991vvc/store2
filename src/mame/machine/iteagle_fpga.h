// license:BSD-3-Clause
// copyright-holders:Ted Green
//*************************************
// iteagle fpga device
//*************************************
<<<<<<< HEAD
#ifndef ITEAGLE_FPGA_H
#define ITEAGLE_FPGA_H

#include "machine/pci.h"
#include "machine/idectrl.h"
#include "machine/eepromser.h"

#define MCFG_ITEAGLE_FPGA_ADD(_tag, _cpu_tag, _irq_num) \
	MCFG_PCI_DEVICE_ADD(_tag, ITEAGLE_FPGA, 0x55CC33AA, 0xAA, 0xAAAAAA, 0x00) \
	downcast<iteagle_fpga_device *>(device)->set_irq_info(_cpu_tag, _irq_num);
=======
#ifndef MAME_MACHINE_ITEAGLE_FPGA_H
#define MAME_MACHINE_ITEAGLE_FPGA_H

#include "machine/pci.h"
#include "machine/nvram.h"
#include "machine/eepromser.h"
#include "machine/z80scc.h"
#include "bus/rs232/rs232.h"

//MCFG_PCI_DEVICE_ADD(_tag, _type, _main_id, _revision, _pclass, _subsystem_id)

#define MCFG_ITEAGLE_FPGA_ADD(_tag, _cpu_tag, _irq_num, _serial_irq_num) \
	MCFG_PCI_DEVICE_ADD(_tag, ITEAGLE_FPGA, 0x55CC33AA, 0xAA, 0xAAAAAA, 0x00) \
	downcast<iteagle_fpga_device *>(device)->set_irq_info(_cpu_tag, _irq_num, _serial_irq_num);
>>>>>>> upstream/master

#define MCFG_ITEAGLE_FPGA_INIT(_version, _seq_init) \
	downcast<iteagle_fpga_device *>(device)->set_init_info(_version, _seq_init);

#define MCFG_ITEAGLE_EEPROM_ADD(_tag) \
<<<<<<< HEAD
	MCFG_PCI_DEVICE_ADD(_tag, ITEAGLE_EEPROM, 0x80861229, 0x00, 0x088000, 0x00)
=======
	MCFG_PCI_DEVICE_ADD(_tag, ITEAGLE_EEPROM, 0x80861229, 0x02, 0x020000, 0x00)
>>>>>>> upstream/master

#define MCFG_ITEAGLE_EEPROM_INIT(_sw_version, _hw_version) \
	downcast<iteagle_eeprom_device *>(device)->set_info(_sw_version, _hw_version);

// Mimic Cypress CY82C693 Peripheral Controller
<<<<<<< HEAD
#define MCFG_ITEAGLE_IDE_ADD(_tag) \
	MCFG_PCI_DEVICE_ADD(_tag, ITEAGLE_IDE, 0x1080C693, 0x00, 0x060100, 0x00)

#define MCFG_ITEAGLE_IDE_IRQ_ADD(_cpu_tag, _irq_num) \
	downcast<iteagle_ide_device *>(device)->set_irq_info(_cpu_tag, _irq_num);

class iteagle_fpga_device : public pci_device,
				public device_nvram_interface
{
public:
	iteagle_fpga_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	void set_init_info(int version, int seq_init) {m_version=version; m_seq_init=seq_init;}
	void set_irq_info(const char *tag, const int irq_num) {m_cpu_tag = tag; m_irq_num = irq_num;}


protected:
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	// device_nvram_interface overrides
	virtual void nvram_default();
	virtual void nvram_read(emu_file &file);
	virtual void nvram_write(emu_file &file);
=======
#define MCFG_ITEAGLE_PERIPH_ADD(_tag) \
	MCFG_PCI_DEVICE_ADD(_tag, ITEAGLE_PERIPH, 0x1080C693, 0x00, 0x060100, 0x00)

// Functional emulation of AMD AM85C30 serial controller
// Two channels, A & B
class iteagle_am85c30
{
public:
	void reset(void);
	void write_control(uint8_t data, int channel);
	uint8_t read_control(int channel);
	void write_data(uint8_t data, int channel);
	uint8_t read_data(int channel);
	void write_rx_str(int channel, std::string resp);
	std::string get_tx_str(int channel) { return m_serial_tx[channel]; };
	void clear_tx_str(int channel) { m_serial_tx[channel].clear(); };
	bool check_interrupt(void) { return (m_rr_regs[0][3] != 0); };
private:
	uint8_t m_rr_regs[2][16];
	uint8_t m_wr_regs[2][16];
	std::string m_serial_tx[2];
	std::string m_serial_rx[2];
};

class iteagle_fpga_device : public pci_device
{
public:
	iteagle_fpga_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	required_device<nvram_device> m_rtc;
	required_device<scc85c30_device> m_scc1;

	void set_init_info(int version, int seq_init) {m_version=version; m_seq_init=seq_init;}
	void set_irq_info(const char *tag, const int irq_num, const int serial_num) {
		m_cpu_tag = tag; m_irq_num = irq_num; m_serial_irq_num = serial_num;}

	DECLARE_WRITE8_MEMBER(serial_rx_w);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr) override;
	virtual void device_add_mconfig(machine_config &config) override;
>>>>>>> upstream/master

private:
	emu_timer *     m_timer;
	const char *m_cpu_tag;
	cpu_device *m_cpu;
	int m_irq_num;
<<<<<<< HEAD

	UINT32 m_fpga_regs[0x20/4];
	UINT32 m_rtc_regs[0x800/4];
	UINT32 m_ram[0x20000/4];
	UINT32 m_prev_reg;

	std::string m_serial_str;
	UINT8 m_serial_idx;
	bool  m_serial_data;
	UINT8 m_serial_com1[0x10];
	UINT8 m_serial_com2[0x10];
	UINT8 m_serial_com3[0x10];
	UINT8 m_serial_com4[0x10];

	UINT32 m_version;
	UINT32 m_seq_init;
	UINT32 m_seq;
	UINT32 m_seq_rem1, m_seq_rem2;
	void update_sequence(UINT32 data);
	void update_sequence_eg1(UINT32 data);
=======
	int m_serial_irq_num;

	uint32_t m_fpga_regs[0x20 / 4];
	uint32_t m_rtc_regs[0x800 / 4];
	uint32_t m_ram[0x20000 / 4];
	uint32_t m_prev_reg;

	uint32_t m_version;
	uint32_t m_seq_init;
	uint32_t m_seq;
	uint32_t m_seq_rem1, m_seq_rem2;

	iteagle_am85c30 m_serial0_1;
	iteagle_am85c30 m_serial2_3;

	void update_sequence(uint32_t data);
	void update_sequence_eg1(uint32_t data);
>>>>>>> upstream/master

	DECLARE_ADDRESS_MAP(rtc_map, 32);
	DECLARE_ADDRESS_MAP(fpga_map, 32);
	DECLARE_ADDRESS_MAP(ram_map, 32);

	DECLARE_READ32_MEMBER( fpga_r );
	DECLARE_WRITE32_MEMBER( fpga_w );
	DECLARE_READ32_MEMBER( rtc_r );
	DECLARE_WRITE32_MEMBER( rtc_w );

	DECLARE_READ32_MEMBER( ram_r );
	DECLARE_WRITE32_MEMBER( ram_w );
<<<<<<< HEAD
=======

	DECLARE_WRITE_LINE_MEMBER(serial_interrupt);
>>>>>>> upstream/master
};

class iteagle_eeprom_device : public pci_device {
public:
<<<<<<< HEAD
	iteagle_eeprom_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	virtual void map_extra(UINT64 memory_window_start, UINT64 memory_window_end, UINT64 memory_offset, address_space *memory_space,
							UINT64 io_window_start, UINT64 io_window_end, UINT64 io_offset, address_space *io_space);

	required_device<eeprom_serial_93cxx_device> m_eeprom;

	void set_info(int sw_version, int hw_version) {m_sw_version=sw_version; m_hw_version=hw_version;}
protected:
	virtual void device_start();
	virtual void device_reset();

private:
	address_space *m_memory_space;
	UINT16 m_sw_version;
	UINT8 m_hw_version;
=======
	iteagle_eeprom_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
	// optional information overrides
	virtual void map_extra(uint64_t memory_window_start, uint64_t memory_window_end, uint64_t memory_offset, address_space *memory_space,
							uint64_t io_window_start, uint64_t io_window_end, uint64_t io_offset, address_space *io_space) override;

	void set_info(int sw_version, int hw_version) {m_sw_version=sw_version; m_hw_version=hw_version;}

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_add_mconfig(machine_config &config) override;

private:
	address_space *m_memory_space;
	uint16_t m_sw_version;
	uint8_t m_hw_version;

	std::array<uint16_t, 0x40> m_iteagle_default_eeprom;
>>>>>>> upstream/master

	DECLARE_ADDRESS_MAP(eeprom_map, 32);
	DECLARE_READ32_MEMBER( eeprom_r );
	DECLARE_WRITE32_MEMBER( eeprom_w );
<<<<<<< HEAD
};

class iteagle_ide_device : public pci_device {
public:
	iteagle_ide_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
	// optional information overrides
	virtual machine_config_constructor device_mconfig_additions() const;
	void set_irq_info(const char *tag, const int irq_num);

	required_device<bus_master_ide_controller_device> m_ide;
	required_device<bus_master_ide_controller_device> m_ide2;
	DECLARE_WRITE_LINE_MEMBER(ide_interrupt);
	DECLARE_WRITE_LINE_MEMBER(ide2_interrupt);

protected:
	virtual void device_start();
	virtual void device_reset();

private:
	const char *m_cpu_tag;
	cpu_device *m_cpu;
	int m_irq_num;
	int m_irq_status;

	UINT32 m_ctrl_regs[0xd0/4];
	UINT8 m_rtc_regs[0x100];

	DECLARE_ADDRESS_MAP(ctrl_map, 32);
	DECLARE_ADDRESS_MAP(ide_map, 32);
	DECLARE_ADDRESS_MAP(ide_ctrl_map, 32);
	DECLARE_ADDRESS_MAP(ide2_map, 32);
	DECLARE_ADDRESS_MAP(ide2_ctrl_map, 32);
=======

	required_device<eeprom_serial_93cxx_device> m_eeprom;
};

class iteagle_periph_device : public pci_device {
public:
	iteagle_periph_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

protected:
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_add_mconfig(machine_config &config) override;

private:
	optional_device<nvram_device> m_rtc;

	uint32_t m_ctrl_regs[0xd0/4];
	uint8_t m_rtc_regs[0x100];

	DECLARE_ADDRESS_MAP(ctrl_map, 32);
>>>>>>> upstream/master

	DECLARE_READ32_MEMBER( ctrl_r );
	DECLARE_WRITE32_MEMBER( ctrl_w );

<<<<<<< HEAD
	DECLARE_READ32_MEMBER( ide_r );
	DECLARE_WRITE32_MEMBER( ide_w );
	DECLARE_READ32_MEMBER( ide_ctrl_r );
	DECLARE_WRITE32_MEMBER( ide_ctrl_w );

	DECLARE_READ32_MEMBER( ide2_r );
	DECLARE_WRITE32_MEMBER( ide2_w );
	DECLARE_READ32_MEMBER( ide2_ctrl_r );
	DECLARE_WRITE32_MEMBER( ide2_ctrl_w );

};

extern const device_type ITEAGLE_FPGA;
extern const device_type ITEAGLE_EEPROM;
extern const device_type ITEAGLE_IDE;

#endif
=======
};

DECLARE_DEVICE_TYPE(ITEAGLE_FPGA, iteagle_fpga_device)
DECLARE_DEVICE_TYPE(ITEAGLE_EEPROM, iteagle_eeprom_device)
DECLARE_DEVICE_TYPE(ITEAGLE_PERIPH, iteagle_periph_device)

#endif // MAME_MACHINE_ITEAGLE_FPGA_H
>>>>>>> upstream/master
