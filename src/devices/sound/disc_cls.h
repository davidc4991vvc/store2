<<<<<<< HEAD
// license:???
// copyright-holders:K.Wilkins, Derrick Renaud, F.Palazzolo, Couriersud
#pragma once

#ifndef __DISC_CLS_H__
#define __DISC_CLS_H__
=======
// license:BSD-3-Clause
// copyright-holders:K.Wilkins,Couriersud,Derrick Renaud,Frank Palazzolo
#ifndef MAME_SOUND_DISC_CLS_H
#define MAME_SOUND_DISC_CLS_H

#pragma once
>>>>>>> upstream/master

/***********************************************************************
 *
 *  MAME - Discrete sound system emulation library
 *
 *  Written by K.Wilkins (mame@esplexo.co.uk)
 *
 *  (c) K.Wilkins 2000
 *
 *  Coding started in November 2000
 *
 *  Additions/bugfix February 2003 - Derrick Renaud, F.Palazzolo, K.Wilkins
 *  Discrete parallel tasks 2009 - Couriersud
 *  Discrete classes 2010        - Couriersud
 *
 ***********************************************************************/

#define DISCRETE_CLASS_NAME(_name) discrete_ ## _name ## _node

#define DISCRETE_CLASS_INPUT(_name, _num)   inline double _name (void) { return *(m_input[_num]); }

#define DISCRETE_CLASS_CONSTRUCTOR(_name, _base)                        \
	public:                                                             \
		DISCRETE_CLASS_NAME(_name)()                                    \
			: DISCRETE_CLASS_NAME(_base)() { }

#define DISCRETE_CLASS_DESTRUCTOR(_name)                                \
	public:                                                             \
		virtual ~ DISCRETE_CLASS_NAME(_name)(void) { }

#define  DISCRETE_CLASS_STEP_RESET(_name, _maxout, _priv)               \
class DISCRETE_CLASS_NAME(_name): public discrete_base_node, public discrete_step_interface         \
{                                                                       \
	DISCRETE_CLASS_CONSTRUCTOR(_name, base)                             \
	DISCRETE_CLASS_DESTRUCTOR(_name)                                    \
public:                                                                 \
<<<<<<< HEAD
	void step(void);                                                    \
	void reset(void);                                                   \
	int max_output(void) { return _maxout; }                    \
=======
	virtual void step(void) override;                                                    \
	virtual void reset(void) override;                                                   \
	virtual int max_output(void) override { return _maxout; }                    \
>>>>>>> upstream/master
private:                                                                \
	_priv                                                               \
}

#define DISCRETE_CLASS_STEP(_name, _maxout, _priv)                      \
class DISCRETE_CLASS_NAME(_name): public discrete_base_node, public discrete_step_interface             \
{                                                                       \
	DISCRETE_CLASS_CONSTRUCTOR(_name, base)                             \
	DISCRETE_CLASS_DESTRUCTOR(_name)                                    \
public:                                                                 \
<<<<<<< HEAD
	void step(void);                                                    \
	void reset(void)            { this->step(); }                       \
	int max_output(void) { return _maxout; }                    \
=======
	virtual void step(void) override;                                   \
	virtual void reset(void) override  { this->step(); }                \
	virtual int max_output(void) override { return _maxout; }           \
>>>>>>> upstream/master
private:                                                                \
	_priv                                                               \
}

#define  DISCRETE_CLASS_RESET(_name, _maxout)                           \
class DISCRETE_CLASS_NAME(_name): public discrete_base_node             \
{                                                                       \
	DISCRETE_CLASS_CONSTRUCTOR(_name, base)                             \
	DISCRETE_CLASS_DESTRUCTOR(_name)                                    \
public:                                                                 \
<<<<<<< HEAD
	void reset(void);                                                   \
	int max_output(void) { return _maxout; }                    \
=======
	virtual void reset(void) override;                                                    \
	virtual int max_output(void) override { return _maxout; }                    \
>>>>>>> upstream/master
}

#define  DISCRETE_CLASS(_name, _maxout, _priv)                      \
class DISCRETE_CLASS_NAME(_name): public discrete_base_node, public discrete_step_interface             \
{                                                                       \
	DISCRETE_CLASS_DESTRUCTOR(_name)                                    \
	DISCRETE_CLASS_CONSTRUCTOR(_name, base)                             \
public:                                                                 \
<<<<<<< HEAD
	void step(void);                                                    \
	void reset(void);                                                   \
	void start(void);                                                   \
	void stop(void);                                                    \
	int max_output(void) { return _maxout; }                    \
=======
	virtual void step(void) override;                                                    \
	virtual void reset(void) override;                                                   \
	virtual void start(void) override;                                                   \
	virtual void stop(void) override;                                                    \
	virtual int max_output(void) override { return _maxout; }                    \
>>>>>>> upstream/master
private:                                                                \
	_priv                                                               \
}

class DISCRETE_CLASS_NAME(special): public discrete_base_node
{
	DISCRETE_CLASS_CONSTRUCTOR(special, base)
	DISCRETE_CLASS_DESTRUCTOR(special)
public:
<<<<<<< HEAD
	int max_output(void) { return 0; }
=======
	virtual int max_output(void) override { return 0; }
>>>>>>> upstream/master
};

class DISCRETE_CLASS_NAME(unimplemented): public discrete_base_node
{
	DISCRETE_CLASS_CONSTRUCTOR(unimplemented, base)
	DISCRETE_CLASS_DESTRUCTOR(unimplemented)
public:
<<<<<<< HEAD
	int max_output(void) { return 0; }
=======
	virtual int max_output(void) override { return 0; }
>>>>>>> upstream/master
};

/*************************************
 *
 *  disc_sys.inc
 *
 *************************************/

class DISCRETE_CLASS_NAME(dso_output):  public discrete_base_node,
										public discrete_sound_output_interface,
										public discrete_step_interface
{
	DISCRETE_CLASS_CONSTRUCTOR(dso_output, base)
	DISCRETE_CLASS_DESTRUCTOR(dso_output)
public:
<<<<<<< HEAD
	void step(void) {
=======
	virtual void step(void) override {
>>>>>>> upstream/master
		/* Add gain to the output and put into the buffers */
		/* Clipping will be handled by the main sound system */
		double val = DISCRETE_INPUT(0) * DISCRETE_INPUT(1);
		*m_ptr++ = val;
	}
<<<<<<< HEAD
	int max_output(void) { return 0; }
	void set_output_ptr(stream_sample_t *ptr) { m_ptr = ptr; }
=======
	virtual int max_output(void) override { return 0; }
	virtual void set_output_ptr(stream_sample_t *ptr) override { m_ptr = ptr; }
>>>>>>> upstream/master
private:
	stream_sample_t     *m_ptr;
};

DISCRETE_CLASS(dso_csvlog, 0,
	FILE *m_csv_file;
<<<<<<< HEAD
	INT64 m_sample_num;
=======
	int64_t m_sample_num;
>>>>>>> upstream/master
	char  m_name[32];
);

DISCRETE_CLASS(dso_wavlog, 0,
	wav_file *m_wavfile;
	char      m_name[32];
);

/*************************************
 *
 *  disc_inp.inc
 *
 *************************************/

class DISCRETE_CLASS_NAME(dss_adjustment): public discrete_base_node, public discrete_step_interface
{
	DISCRETE_CLASS_CONSTRUCTOR(dss_adjustment, base)
	DISCRETE_CLASS_DESTRUCTOR(dss_adjustment)
public:
<<<<<<< HEAD
	void step(void);
	void reset(void);
private:
	ioport_port *m_port;
	INT32                   m_lastpval;
	INT32                   m_pmin;
=======
	virtual void step(void) override;
	virtual void reset(void) override;
private:
	ioport_port *m_port;
	int32_t                   m_lastpval;
	int32_t                   m_pmin;
>>>>>>> upstream/master
	double                  m_pscale;
	double                  m_min;
	double                  m_scale;
};

DISCRETE_CLASS_RESET(dss_constant, 1);

class DISCRETE_CLASS_NAME(dss_input_data): public discrete_base_node, public discrete_input_interface
{
	DISCRETE_CLASS_DESTRUCTOR(dss_input_data)
	DISCRETE_CLASS_CONSTRUCTOR(dss_input_data, base)
public:
<<<<<<< HEAD
	void reset(void);
	void input_write(int sub_node, UINT8 data );
private:
	double      m_gain;             /* node gain */
	double      m_offset;           /* node offset */
	UINT8       m_data;             /* data written */
=======
	virtual void reset(void) override;
	virtual void input_write(int sub_node, uint8_t data ) override;
private:
	double      m_gain;             /* node gain */
	double      m_offset;           /* node offset */
	uint8_t       m_data;             /* data written */
>>>>>>> upstream/master
};

class DISCRETE_CLASS_NAME(dss_input_logic): public discrete_base_node, public discrete_input_interface
{
	DISCRETE_CLASS_CONSTRUCTOR(dss_input_logic, base)
	DISCRETE_CLASS_DESTRUCTOR(dss_input_logic)
public:
<<<<<<< HEAD
	void reset(void);
	void input_write(int sub_node, UINT8 data );
private:
	double      m_gain;             /* node gain */
	double      m_offset;           /* node offset */
	UINT8       m_data;             /* data written */
=======
	virtual void reset(void) override;
	virtual void input_write(int sub_node, uint8_t data ) override;
private:
	double      m_gain;             /* node gain */
	double      m_offset;           /* node offset */
	uint8_t       m_data;             /* data written */
>>>>>>> upstream/master
};

class DISCRETE_CLASS_NAME(dss_input_not): public discrete_base_node, public discrete_input_interface
{
	DISCRETE_CLASS_CONSTRUCTOR(dss_input_not, base)
	DISCRETE_CLASS_DESTRUCTOR(dss_input_not)
public:
<<<<<<< HEAD
	void reset(void);
	void input_write(int sub_node, UINT8 data );
private:
	double      m_gain;             /* node gain */
	double      m_offset;           /* node offset */
	UINT8       m_data;             /* data written */
=======
	virtual void reset(void) override;
	virtual void input_write(int sub_node, uint8_t data ) override;
private:
	double      m_gain;             /* node gain */
	double      m_offset;           /* node offset */
	uint8_t       m_data;             /* data written */
>>>>>>> upstream/master
};

class DISCRETE_CLASS_NAME(dss_input_pulse): public discrete_base_node, public discrete_input_interface, public discrete_step_interface
{
	DISCRETE_CLASS_CONSTRUCTOR(dss_input_pulse, base)
	DISCRETE_CLASS_DESTRUCTOR(dss_input_pulse)
public:
<<<<<<< HEAD
	void step(void);
	void reset(void);
	void input_write(int sub_node, UINT8 data );
private:
	//double      m_gain;             /* node gain */
	//double      m_offset;           /* node offset */
	UINT8       m_data;             /* data written */
=======
	virtual void step(void) override;
	virtual void reset(void) override;
	virtual void input_write(int sub_node, uint8_t data ) override;
private:
	//double      m_gain;             /* node gain */
	//double      m_offset;           /* node offset */
	uint8_t       m_data;             /* data written */
>>>>>>> upstream/master
};

class DISCRETE_CLASS_NAME(dss_input_stream): public discrete_base_node, public discrete_input_interface, public discrete_step_interface
{
	DISCRETE_CLASS_CONSTRUCTOR(dss_input_stream, base)
	DISCRETE_CLASS_DESTRUCTOR(dss_input_stream)
public:
<<<<<<< HEAD
	void step(void);
	void reset(void);
	void start(void);
	void input_write(int sub_node, UINT8 data );
=======
	virtual void step(void) override;
	virtual void reset(void) override;
	virtual void start(void) override;
	virtual void input_write(int sub_node, uint8_t data ) override;
>>>>>>> upstream/master
	virtual bool is_buffered(void) { return false; }

	/* This is called by discrete_sound_device */
	void stream_start(void);

//protected:
<<<<<<< HEAD
	UINT32              m_stream_in_number;
=======
	uint32_t              m_stream_in_number;
>>>>>>> upstream/master
	stream_sample_t     *m_ptr;         /* current in ptr for stream */
private:
	void stream_generate(sound_stream &stream, stream_sample_t **inputs, stream_sample_t **outputs, int samples);

	double      m_gain;             /* node gain */
	double      m_offset;           /* node offset */
<<<<<<< HEAD
	UINT8       m_data;             /* data written */
	UINT8               m_is_buffered;
=======
	uint8_t       m_data;             /* data written */
	uint8_t               m_is_buffered;
>>>>>>> upstream/master
	/* the buffer stream */
	sound_stream        *m_buffer_stream;
};

class DISCRETE_CLASS_NAME(dss_input_buffer): public DISCRETE_CLASS_NAME(dss_input_stream)
{
	DISCRETE_CLASS_CONSTRUCTOR(dss_input_buffer, dss_input_stream)
	DISCRETE_CLASS_DESTRUCTOR(dss_input_buffer)
public:
<<<<<<< HEAD
	bool is_buffered(void) { return true; }
=======
	virtual bool is_buffered(void) override { return true; }
>>>>>>> upstream/master
};

#include "disc_wav.h"
#include "disc_mth.h"
#include "disc_flt.h"
#include "disc_dev.h"

<<<<<<< HEAD
#endif /* __DISCRETE_H__ */
=======
#endif // MAME_SOUND_DISC_CLS_H
>>>>>>> upstream/master
