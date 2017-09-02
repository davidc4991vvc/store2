// license:BSD-3-Clause
// copyright-holders:Aaron Giles
<<<<<<< HEAD
typedef UINT8 (*segag80_decrypt_func)(offs_t, UINT8);
=======
typedef uint8_t (*segag80_decrypt_func)(offs_t, uint8_t);
>>>>>>> upstream/master

segag80_decrypt_func segag80_security(int chip);
