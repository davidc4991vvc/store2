<<<<<<< HEAD
// license:BSD-3
// copyright-holders:Andreas Naive

#ifndef _NS10CRYPT_H_
#define _NS10CRYPT_H_

class gf2_reducer  // helper class
{
public:
	gf2_reducer();
	int gf2_reduce(UINT64 num)const;
private:
	int _gf2Reduction[0x10000];
};

class ns10_decrypter_device : public device_t
{
public:
=======
// license:BSD-3-Clause
// copyright-holders:Andreas Naive

#ifndef MAME_MACHINE_NS10CRYPT_H
#define MAME_MACHINE_NS10CRYPT_H

#include <cstdint>

class ns10_decrypter_device : public device_t
{
public:
	void activate(int iv);
	void deactivate();
	bool is_active()const;

	virtual uint16_t decrypt(uint16_t cipherword)=0;
	virtual ~ns10_decrypter_device();

protected:
	ns10_decrypter_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

	virtual void init(int iv)=0;
	virtual void device_start()override=0;

	bool _active;
};

class ns10_type1_decrypter_device : public ns10_decrypter_device
{
public:
	// with just only type-1 game known, we cannot say which parts of the crypto_logic is common, if any,
	// and which is game-specific. In practice, this class is just an alias for the decrypter device of mrdrilr2
	uint16_t decrypt(uint16_t cipherword)override;

protected:
	ns10_type1_decrypter_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock);

private:
	uint16_t _mask;
	uint8_t _counter;
	static const int initSbox[16];

	void init(int iv)override;
	void device_start()override;
};


class ns10_type2_decrypter_device : public ns10_decrypter_device
{
public:
	uint16_t decrypt(uint16_t cipherword)override;

protected:
	class gf2_reducer  // helper class
	{
	public:
		gf2_reducer();
		int gf2_reduce(uint64_t num)const;
	private:
		int _gf2Reduction[0x10000];
	};

>>>>>>> upstream/master
	// this encodes the decryption logic, which varies per game
	// and is probably hard-coded into the CPLD
	struct ns10_crypto_logic
	{
<<<<<<< HEAD
		UINT64 eMask[16];
		UINT64 dMask[16];
		UINT16 xMask;
		UINT16(*nonlinear_calculation)(UINT64, UINT64, const gf2_reducer&);  // preliminary encoding; need research
	};

	void activate(int iv);
	void deactivate();
	bool is_active()const;

	UINT16 decrypt(UINT16 cipherword);

protected:
	ns10_decrypter_device(
		device_type type, const ns10_decrypter_device::ns10_crypto_logic &logic,
		const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

private:
	UINT16 _mask;
	UINT64 _previous_cipherwords;
	UINT64 _previous_plainwords;
	bool _active;
	const ns10_crypto_logic& _logic;
	static const int initSbox[16];
	const gf2_reducer *_reducer;

	void device_start();
	void init(int iv);
=======
		uint64_t eMask[16];
		uint64_t dMask[16];
		uint16_t xMask;
		uint16_t(*nonlinear_calculation)(uint64_t, uint64_t, const gf2_reducer&);  // preliminary encoding; need research
	};

	ns10_type2_decrypter_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock, const ns10_crypto_logic &logic);

private:
	uint16_t _mask;
	uint64_t _previous_cipherwords;
	uint64_t _previous_plainwords;
	const ns10_crypto_logic& _logic;
	std::unique_ptr<const gf2_reducer>_reducer;
	static const int initSbox[16];

	void init(int iv)override;
	void device_start()override;
>>>>>>> upstream/master
};



// game-specific devices

<<<<<<< HEAD
class chocovdr_decrypter_device : public ns10_decrypter_device
{
public:
	chocovdr_decrypter_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};

class gamshara_decrypter_device : public ns10_decrypter_device
{
public:
	gamshara_decrypter_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};

class gjspace_decrypter_device : public ns10_decrypter_device
{
public:
	gjspace_decrypter_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};

class knpuzzle_decrypter_device : public ns10_decrypter_device
{
public:
	knpuzzle_decrypter_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};

class konotako_decrypter_device : public ns10_decrypter_device
{
public:
	konotako_decrypter_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};

class nflclsfb_decrypter_device : public ns10_decrypter_device
{
public:
	nflclsfb_decrypter_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};

class startrgn_decrypter_device : public ns10_decrypter_device
{
public:
	startrgn_decrypter_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};


extern const device_type CHOCOVDR_DECRYPTER;
extern const device_type GAMSHARA_DECRYPTER;
extern const device_type  GJSPACE_DECRYPTER;
extern const device_type KNPUZZLE_DECRYPTER;
extern const device_type KONOTAKO_DECRYPTER;
extern const device_type NFLCLSFB_DECRYPTER;
extern const device_type STARTRGN_DECRYPTER;

#endif
=======
class mrdrilr2_decrypter_device : public ns10_type1_decrypter_device
{
public:
	mrdrilr2_decrypter_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
};

class chocovdr_decrypter_device : public ns10_type2_decrypter_device
{
public:
	chocovdr_decrypter_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
private:
	static uint16_t nonlinear_calc(uint64_t previous_cipherwords, uint64_t previous_plainwords, const gf2_reducer &reducer);
	static const ns10_crypto_logic crypto_logic;
};

class gamshara_decrypter_device : public ns10_type2_decrypter_device
{
public:
	gamshara_decrypter_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
private:
	static uint16_t nonlinear_calc(uint64_t previous_cipherwords, uint64_t previous_plainwords, const gf2_reducer &reducer);
	static const ns10_crypto_logic crypto_logic;
};

class gjspace_decrypter_device : public ns10_type2_decrypter_device
{
public:
	gjspace_decrypter_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
private:
	static uint16_t nonlinear_calc(uint64_t previous_cipherwords, uint64_t previous_plainwords, const gf2_reducer &reducer);
	static const ns10_crypto_logic crypto_logic;
};

class knpuzzle_decrypter_device : public ns10_type2_decrypter_device
{
public:
	knpuzzle_decrypter_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
private:
	static uint16_t nonlinear_calc(uint64_t previous_cipherwords, uint64_t previous_plainwords, const gf2_reducer &reducer);
	static const ns10_crypto_logic crypto_logic;
};

class konotako_decrypter_device : public ns10_type2_decrypter_device
{
public:
	konotako_decrypter_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
private:
	static uint16_t nonlinear_calc(uint64_t previous_cipherwords, uint64_t previous_plainwords, const gf2_reducer &reducer);
	static const ns10_crypto_logic crypto_logic;
};

class nflclsfb_decrypter_device : public ns10_type2_decrypter_device
{
public:
	nflclsfb_decrypter_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
private:
	static uint16_t nonlinear_calc(uint64_t previous_cipherwords, uint64_t previous_plainwords, const gf2_reducer &reducer);
	static const ns10_crypto_logic crypto_logic;
};

class startrgn_decrypter_device : public ns10_type2_decrypter_device
{
public:
	startrgn_decrypter_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);
private:
	static uint16_t nonlinear_calc(uint64_t previous_cipherwords, uint64_t previous_plainwords, const gf2_reducer &reducer);
	static const ns10_crypto_logic crypto_logic;
};


DECLARE_DEVICE_TYPE(CHOCOVDR_DECRYPTER, chocovdr_decrypter_device)
DECLARE_DEVICE_TYPE(GAMSHARA_DECRYPTER, gamshara_decrypter_device)
DECLARE_DEVICE_TYPE(GJSPACE_DECRYPTER,  gjspace_decrypter_device)
DECLARE_DEVICE_TYPE(KNPUZZLE_DECRYPTER, knpuzzle_decrypter_device)
DECLARE_DEVICE_TYPE(KONOTAKO_DECRYPTER, konotako_decrypter_device)
DECLARE_DEVICE_TYPE(MRDRILR2_DECRYPTER, mrdrilr2_decrypter_device)
DECLARE_DEVICE_TYPE(NFLCLSFB_DECRYPTER, nflclsfb_decrypter_device)
DECLARE_DEVICE_TYPE(STARTRGN_DECRYPTER, startrgn_decrypter_device)

#endif // MAME_MACHINE_NS10CRYPT_H
>>>>>>> upstream/master
