// license:BSD-3-Clause
// copyright-holders:R. Belmont
/***************************************************************************

  nubus_image.c - synthetic NuBus card to allow reading/writing "raw"
  HFS images, including floppy images (DD and HD) and vMac/Basilisk HDD
  volumes up to 256 MB in size.

***************************************************************************/

#include "emu.h"
#include "nubus_image.h"
#include "osdcore.h"

#define IMAGE_ROM_REGION    "image_rom"
#define IMAGE_DISK0_TAG     "nb_disk"

#define MESSIMG_DISK_SECTOR_SIZE (512)

<<<<<<< HEAD
// on big-endian, these are NOPs.  (TODO: hey, where did WORDS_BIGENDIAN go since the GENie transition?!)
#if defined(__ppc__) || defined (__PPC__) || defined(__ppc64__) || defined(__PPC64__)
static UINT32 ni_htonl(UINT32 x) { return x; }
static UINT32 ni_ntohl(UINT32 x) { return x; }
#else
static UINT32 ni_htonl(UINT32 x) { return FLIPENDIAN_INT32(x); }
static UINT32 ni_ntohl(UINT32 x) { return FLIPENDIAN_INT32(x); }
#endif


// messimg_disk_image_device

class messimg_disk_image_device :   public device_t,
=======

// nubus_image_device::messimg_disk_image_device

class nubus_image_device::messimg_disk_image_device :   public device_t,
>>>>>>> upstream/master
								public device_image_interface
{
public:
	// construction/destruction
<<<<<<< HEAD
	messimg_disk_image_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// image-level overrides
	virtual iodevice_t image_type() const { return IO_QUICKLOAD; }

	virtual bool is_readable()  const { return 1; }
	virtual bool is_writeable() const { return 1; }
	virtual bool is_creatable() const { return 0; }
	virtual bool must_be_loaded() const { return 0; }
	virtual bool is_reset_on_load() const { return 0; }
	virtual const char *image_interface() const { return NULL; }
	virtual const char *file_extensions() const { return "img"; }
	virtual const option_guide *create_option_guide() const { return NULL; }

	virtual bool call_load();
	virtual void call_unload();

	protected:
	// device-level overrides
	virtual void device_config_complete();
	virtual void device_start();
	virtual void device_reset();
public:
	UINT32 m_size;
	UINT8 *m_data;
=======
	messimg_disk_image_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	// image-level overrides
	virtual iodevice_t image_type() const override { return IO_QUICKLOAD; }

	virtual bool is_readable()  const override { return 1; }
	virtual bool is_writeable() const override { return 1; }
	virtual bool is_creatable() const override { return 0; }
	virtual bool must_be_loaded() const override { return 0; }
	virtual bool is_reset_on_load() const override { return 0; }
	virtual const char *file_extensions() const override { return "img"; }
	virtual const char *custom_instance_name() const override { return "disk"; }
	virtual const char *custom_brief_instance_name() const override { return "disk"; }

	virtual image_init_result call_load() override;
	virtual void call_unload() override;

	protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
public:
	uint32_t m_size;
	std::unique_ptr<uint8_t[]> m_data;
>>>>>>> upstream/master
	bool m_ejected;
};


// device type definition
<<<<<<< HEAD
extern const device_type MESSIMG_DISK;

const device_type MESSIMG_DISK = &device_creator<messimg_disk_image_device>;

messimg_disk_image_device::messimg_disk_image_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock)
	: device_t(mconfig, MESSIMG_DISK, "Mac image", tag, owner, clock, "messimg_disk_image", __FILE__),
		device_image_interface(mconfig, *this), m_size(0), m_data(nullptr), m_ejected(false)
{
}

void messimg_disk_image_device::device_config_complete()
{
	update_names(MESSIMG_DISK, "disk", "disk");
=======
DEFINE_DEVICE_TYPE_NS(MESSIMG_DISK, nubus_image_device, messimg_disk_image_device, "messimg_disk_image", "Mac image")

nubus_image_device::messimg_disk_image_device::messimg_disk_image_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, MESSIMG_DISK, tag, owner, clock),
	device_image_interface(mconfig, *this),
	m_size(0), m_data(nullptr), m_ejected(false)
{
>>>>>>> upstream/master
}


/*-------------------------------------------------
    device start callback
-------------------------------------------------*/

<<<<<<< HEAD
void messimg_disk_image_device::device_start()
{
	m_data = (UINT8 *)NULL;

	if (exists() && fseek(0, SEEK_END) == 0)
	{
		m_size = (UINT32)ftell();
	}
}

bool messimg_disk_image_device::call_load()
{
	fseek(0, SEEK_END);
	m_size = (UINT32)ftell();
=======
void nubus_image_device::messimg_disk_image_device::device_start()
{
	m_data = nullptr;

	if (exists() && fseek(0, SEEK_END) == 0)
	{
		m_size = (uint32_t)ftell();
	}
}

image_init_result nubus_image_device::messimg_disk_image_device::call_load()
{
	fseek(0, SEEK_END);
	m_size = (uint32_t)ftell();
>>>>>>> upstream/master
	if (m_size > (256*1024*1024))
	{
		printf("Mac image too large: must be 256MB or less!\n");
		m_size = 0;
<<<<<<< HEAD
		return IMAGE_INIT_FAIL;
	}

	m_data = (UINT8 *)auto_alloc_array_clear(machine(), UINT32, m_size/sizeof(UINT32));
	fseek(0, SEEK_SET);
	fread(m_data, m_size);
	m_ejected = false;

	return IMAGE_INIT_PASS;
}

void messimg_disk_image_device::call_unload()
{
	// TODO: track dirty sectors and only write those
	fseek(0, SEEK_SET);
	fwrite(m_data, m_size);
=======
		return image_init_result::FAIL;
	}

	m_data = make_unique_clear<uint8_t[]>(m_size);
	fseek(0, SEEK_SET);
	fread(m_data.get(), m_size);
	m_ejected = false;

	return image_init_result::PASS;
}

void nubus_image_device::messimg_disk_image_device::call_unload()
{
	// TODO: track dirty sectors and only write those
	fseek(0, SEEK_SET);
	fwrite(m_data.get(), m_size);
>>>>>>> upstream/master
	m_size = 0;
	//free(m_data);
}

/*-------------------------------------------------
    device reset callback
-------------------------------------------------*/

<<<<<<< HEAD
void messimg_disk_image_device::device_reset()
{
}

MACHINE_CONFIG_FRAGMENT( image )
	MCFG_DEVICE_ADD(IMAGE_DISK0_TAG, MESSIMG_DISK, 0)
MACHINE_CONFIG_END

=======
void nubus_image_device::messimg_disk_image_device::device_reset()
{
}

>>>>>>> upstream/master
ROM_START( image )
	ROM_REGION(0x2000, IMAGE_ROM_REGION, 0)
	ROM_LOAD( "nb_fake.bin",  0x000000, 0x002000, CRC(9264bac5) SHA1(540c2ce3c90382b2da6e1e21182cdf8fc3f0c930) )
ROM_END

//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

<<<<<<< HEAD
const device_type NUBUS_IMAGE = &device_creator<nubus_image_device>;


//-------------------------------------------------
//  machine_config_additions - device-specific
//  machine configurations
//-------------------------------------------------

machine_config_constructor nubus_image_device::device_mconfig_additions() const
{
	return MACHINE_CONFIG_NAME( image );
}
=======
DEFINE_DEVICE_TYPE(NUBUS_IMAGE, nubus_image_device, "nb_image", "NuBus Disk Image Pseudo-Card")


//-------------------------------------------------
//  device_add_mconfig - add device configuration
//-------------------------------------------------

MACHINE_CONFIG_MEMBER( nubus_image_device::device_add_mconfig )
	MCFG_DEVICE_ADD(IMAGE_DISK0_TAG, MESSIMG_DISK, 0)
MACHINE_CONFIG_END
>>>>>>> upstream/master

//-------------------------------------------------
//  rom_region - device-specific ROM region
//-------------------------------------------------

<<<<<<< HEAD
const rom_entry *nubus_image_device::device_rom_region() const
=======
const tiny_rom_entry *nubus_image_device::device_rom_region() const
>>>>>>> upstream/master
{
	return ROM_NAME( image );
}

//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  nubus_image_device - constructor
//-------------------------------------------------

<<<<<<< HEAD
nubus_image_device::nubus_image_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
		device_t(mconfig, NUBUS_IMAGE, "Disk Image Pseudo-Card", tag, owner, clock, "nb_image", __FILE__),
		device_nubus_card_interface(mconfig, *this), m_image(nullptr)
{
}

nubus_image_device::nubus_image_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, const char *shortname, const char *source) :
		device_t(mconfig, type, name, tag, owner, clock, shortname, source),
		device_nubus_card_interface(mconfig, *this), m_image(nullptr)
=======
nubus_image_device::nubus_image_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock) :
	nubus_image_device(mconfig, NUBUS_IMAGE, tag, owner, clock)
{
}

nubus_image_device::nubus_image_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock) :
	device_t(mconfig, type, tag, owner, clock),
	device_nubus_card_interface(mconfig, *this),
	m_image(nullptr)
>>>>>>> upstream/master
{
}

//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void nubus_image_device::device_start()
{
<<<<<<< HEAD
	UINT32 slotspace;
	UINT32 superslotspace;
=======
	uint32_t slotspace;
	uint32_t superslotspace;
>>>>>>> upstream/master

	// set_nubus_device makes m_slot valid
	set_nubus_device();
	install_declaration_rom(this, IMAGE_ROM_REGION);

	slotspace = get_slotspace();
	superslotspace = get_super_slotspace();

//  printf("[image %p] slotspace = %x, super = %x\n", this, slotspace, superslotspace);

	m_nubus->install_device(slotspace, slotspace+3, read32_delegate(FUNC(nubus_image_device::image_r), this), write32_delegate(FUNC(nubus_image_device::image_w), this));
	m_nubus->install_device(slotspace+4, slotspace+7, read32_delegate(FUNC(nubus_image_device::image_status_r), this), write32_delegate(FUNC(nubus_image_device::image_status_w), this));
	m_nubus->install_device(slotspace+8, slotspace+11, read32_delegate(FUNC(nubus_image_device::file_cmd_r), this), write32_delegate(FUNC(nubus_image_device::file_cmd_w), this));
	m_nubus->install_device(slotspace+12, slotspace+15, read32_delegate(FUNC(nubus_image_device::file_data_r), this), write32_delegate(FUNC(nubus_image_device::file_data_w), this));
	m_nubus->install_device(slotspace+16, slotspace+19, read32_delegate(FUNC(nubus_image_device::file_len_r), this), write32_delegate(FUNC(nubus_image_device::file_len_w), this));
	m_nubus->install_device(slotspace+20, slotspace+147, read32_delegate(FUNC(nubus_image_device::file_name_r), this), write32_delegate(FUNC(nubus_image_device::file_name_w), this));
	m_nubus->install_device(superslotspace, superslotspace+((256*1024*1024)-1), read32_delegate(FUNC(nubus_image_device::image_super_r), this), write32_delegate(FUNC(nubus_image_device::image_super_w), this));

	m_image = subdevice<messimg_disk_image_device>(IMAGE_DISK0_TAG);

	filectx.curdir[0] = '.';
	filectx.curdir[1] = '\0';
<<<<<<< HEAD
	filectx.dirp = NULL;
	filectx.fd = NULL;
=======
	filectx.dirp = nullptr;
	filectx.fd = nullptr;
>>>>>>> upstream/master
}

//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void nubus_image_device::device_reset()
{
}

WRITE32_MEMBER( nubus_image_device::image_status_w )
{
	m_image->m_ejected = true;
}

READ32_MEMBER( nubus_image_device::image_status_r )
{
	if(m_image->m_ejected) {
		return 0;
	}

	if(m_image->m_size) {
		return 1;
	}
	return 0;
}

WRITE32_MEMBER( nubus_image_device::image_w )
{
}

READ32_MEMBER( nubus_image_device::image_r )
{
	return m_image->m_size;
}

WRITE32_MEMBER( nubus_image_device::image_super_w )
{
<<<<<<< HEAD
	UINT32 *image = (UINT32*)m_image->m_data;
=======
	uint32_t *image = (uint32_t*)m_image->m_data.get();
>>>>>>> upstream/master
	data = ((data & 0xff) << 24) | ((data & 0xff00) << 8) | ((data & 0xff0000) >> 8) | ((data & 0xff000000) >> 24);
	mem_mask = ((mem_mask & 0xff) << 24) | ((mem_mask & 0xff00) << 8) | ((mem_mask & 0xff0000) >> 8) | ((mem_mask & 0xff000000) >> 24);

	COMBINE_DATA(&image[offset]);
}

READ32_MEMBER( nubus_image_device::image_super_r )
{
<<<<<<< HEAD
	UINT32 *image = (UINT32*)m_image->m_data;
	UINT32 data = image[offset];
=======
	uint32_t *image = (uint32_t*)m_image->m_data.get();
	uint32_t data = image[offset];
>>>>>>> upstream/master
	return ((data & 0xff) << 24) | ((data & 0xff00) << 8) | ((data & 0xff0000) >> 8) | ((data & 0xff000000) >> 24);
}

WRITE32_MEMBER( nubus_image_device::file_cmd_w )
{
<<<<<<< HEAD
	const osd_directory_entry *dp = NULL;
	char fullpath[1024];
	UINT64 filesize;
=======
	const osd::directory::entry *dp;
	char fullpath[1024];
	uint64_t filesize;
>>>>>>> upstream/master

//  data = ((data & 0xff) << 24) | ((data & 0xff00) << 8) | ((data & 0xff0000) >> 8) | ((data & 0xff000000) >> 24);
	filectx.curcmd = data;
	switch(data) {
	case kFileCmdGetDir:
		strcpy((char*)filectx.filename, (char*)filectx.curdir);
		break;
	case kFileCmdSetDir:
		if ((filectx.filename[0] == '/') || (filectx.filename[0] == '$')) {
			strcpy((char*)filectx.curdir, (char*)filectx.filename);
		} else {
			strcat((char*)filectx.curdir, "/");
			strcat((char*)filectx.curdir, (char*)filectx.filename);
		}
		break;
	case kFileCmdGetFirstListing:
<<<<<<< HEAD
		if(filectx.dirp) osd_closedir(filectx.dirp);
		filectx.dirp = osd_opendir((const char *)filectx.curdir);
	case kFileCmdGetNextListing:
		if (filectx.dirp) {
			dp = osd_readdir(filectx.dirp);
=======
		filectx.dirp = osd::directory::open((const char *)filectx.curdir);
	case kFileCmdGetNextListing:
		if (filectx.dirp) {
			dp = filectx.dirp->read();
>>>>>>> upstream/master
			if(dp) {
				strncpy((char*)filectx.filename, dp->name, sizeof(filectx.filename));
			} else {
				memset(filectx.filename, 0, sizeof(filectx.filename));
			}
		}
		else {
			memset(filectx.filename, 0, sizeof(filectx.filename));
		}
		break;
	case kFileCmdGetFile:
		memset(fullpath, 0, sizeof(fullpath));
		strcpy(fullpath, (const char *)filectx.curdir);
		strcat(fullpath, "/");
		strcat(fullpath, (const char*)filectx.filename);
<<<<<<< HEAD
		if(osd_open((const char*)fullpath, OPEN_FLAG_READ, &filectx.fd, &filectx.filelen) != FILERR_NONE) printf("Error opening %s\n", fullpath);
=======
		if(osd_file::open(std::string(fullpath), OPEN_FLAG_READ, filectx.fd, filectx.filelen) != osd_file::error::NONE) printf("Error opening %s\n", fullpath);
>>>>>>> upstream/master
		filectx.bytecount = 0;
		break;
	case kFileCmdPutFile:
		memset(fullpath, 0, sizeof(fullpath));
		strcpy(fullpath, (const char *)filectx.curdir);
		strcat(fullpath, "/");
		strcat(fullpath, (const char*)filectx.filename);
<<<<<<< HEAD
		if(osd_open((const char*)fullpath, OPEN_FLAG_WRITE|OPEN_FLAG_CREATE, &filectx.fd, &filesize) != FILERR_NONE) printf("Error opening %s\n", fullpath);
=======
		if(osd_file::open(std::string(fullpath), OPEN_FLAG_WRITE|OPEN_FLAG_CREATE, filectx.fd, filesize) != osd_file::error::NONE) printf("Error opening %s\n", fullpath);
>>>>>>> upstream/master
		filectx.bytecount = 0;
		break;
	}
}

READ32_MEMBER( nubus_image_device::file_cmd_r )
{
	return 0;
}

WRITE32_MEMBER( nubus_image_device::file_data_w )
{
<<<<<<< HEAD
	UINT32 count = 4;
	UINT32 actualcount = 0;

	data = ((data & 0xff) << 24) | ((data & 0xff00) << 8) | ((data & 0xff0000) >> 8) | ((data & 0xff000000) >> 24);
	if(filectx.fd != NULL) {
		//data = ni_ntohl(data);
		if((filectx.bytecount + count) > filectx.filelen) count = filectx.filelen - filectx.bytecount;
		osd_write(filectx.fd, &data, filectx.bytecount, count, &actualcount);
		filectx.bytecount += actualcount;

		if(filectx.bytecount >= filectx.filelen) {
			osd_close(filectx.fd);
			filectx.fd = NULL;
=======
	std::uint32_t count = 4;
	std::uint32_t actualcount = 0;

	data = ((data & 0xff) << 24) | ((data & 0xff00) << 8) | ((data & 0xff0000) >> 8) | ((data & 0xff000000) >> 24);
	if(filectx.fd) {
		//data = big_endianize_int32(data);
		if((filectx.bytecount + count) > filectx.filelen) count = filectx.filelen - filectx.bytecount;
		filectx.fd->write(&data, filectx.bytecount, count, actualcount);
		filectx.bytecount += actualcount;

		if(filectx.bytecount >= filectx.filelen) {
			filectx.fd.reset();
>>>>>>> upstream/master
		}
	}
}

READ32_MEMBER( nubus_image_device::file_data_r )
{
<<<<<<< HEAD
	if(filectx.fd != NULL) {
		UINT32 ret;
		UINT32 actual = 0;
		osd_read(filectx.fd, &ret, filectx.bytecount, sizeof(ret), &actual);
		filectx.bytecount += actual;
		if(actual < sizeof(ret)) {
			osd_close(filectx.fd);
			filectx.fd = NULL;
		}
		return ni_htonl(ret);
=======
	if(filectx.fd) {
		std::uint32_t ret;
		std::uint32_t actual = 0;
		filectx.fd->read(&ret, filectx.bytecount, sizeof(ret), actual);
		filectx.bytecount += actual;
		if(actual < sizeof(ret)) {
			filectx.fd.reset();
		}
		return big_endianize_int32(ret);
>>>>>>> upstream/master
	}
	return 0;
}

WRITE32_MEMBER( nubus_image_device::file_len_w )
{
	data = ((data & 0xff) << 24) | ((data & 0xff00) << 8) | ((data & 0xff0000) >> 8) | ((data & 0xff000000) >> 24);
<<<<<<< HEAD
	filectx.filelen = ni_ntohl(data);
=======
	filectx.filelen = big_endianize_int32(data);
>>>>>>> upstream/master
}

READ32_MEMBER( nubus_image_device::file_len_r )
{
	return filectx.filelen;
}

WRITE32_MEMBER( nubus_image_device::file_name_w )
{
<<<<<<< HEAD
	((UINT32*)(filectx.filename))[offset] = ni_ntohl(data);
=======
	((uint32_t*)(filectx.filename))[offset] = big_endianize_int32(data);
>>>>>>> upstream/master
}

READ32_MEMBER( nubus_image_device::file_name_r )
{
<<<<<<< HEAD
	UINT32 ret;
	ret = ni_htonl(((UINT32*)(filectx.filename))[offset]);
=======
	uint32_t ret;
	ret = big_endianize_int32(((uint32_t*)(filectx.filename))[offset]);
>>>>>>> upstream/master
	return ret;
}
