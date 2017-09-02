// license:BSD-3-Clause
// copyright-holders:Carl
<<<<<<< HEAD
#if defined(OSD_NET_USE_PCAP)

#if defined(SDLMAME_WIN32) || defined(OSD_WINDOWS)
#ifdef UNICODE
#define LIB_NAME        L"wpcap.dll"
#define LoadDynamicLibrary LoadLibraryW
#else
#define LIB_NAME        "wpcap.dll"
#define LoadDynamicLibrary LoadLibraryA
#endif
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <pcap.h>
=======

#if defined(OSD_NET_USE_PCAP)
>>>>>>> upstream/master

#include "emu.h"
#include "osdnet.h"
#include "netdev_module.h"
#include "modules/osdmodule.h"
<<<<<<< HEAD

#if defined(SDLMAME_WIN32) || defined(OSD_WINDOWS)

#define LIB_ERROR_STR   "Unable to load winpcap: %lx\n"
typedef DWORD except_type;

#else

#include <dlfcn.h>
#ifdef SDLMAME_MACOSX
#include <pthread.h>
#include <libkern/OSAtomic.h>
#endif

#ifdef SDLMAME_MACOSX
#define LIB_NAME    "libpcap.dylib"
#else
#define LIB_NAME    "libpcap.so"
#endif
#define LIB_ERROR_STR   "Unable to load pcap: %s\n"

typedef void *HMODULE;
typedef const char *except_type;
#define FreeLibrary(x) dlclose(x)
#define GetLastError() dlerror()
#define GetProcAddress(x, y) dlsym(x, y)
#define LoadDynamicLibrary(x) dlopen(x, RTLD_LAZY)

#endif
=======
#include "modules/lib/osdlib.h"

#if defined(SDLMAME_WIN32) || defined(OSD_WINDOWS)
#include <windows.h>
#undef interface
#define LIB_NAME    "wpcap.dll"

#elif defined(SDLMAME_MACOSX)
#include <pthread.h>
#include <libkern/OSAtomic.h>
#define LIB_NAME    "libpcap.dylib"

#else
#define LIB_NAME    "libpcap.so"
#endif

#include <pcap.h>

// Typedefs for dynamically loaded functions
typedef int (*pcap_findalldevs_fn)(pcap_if_t **, char *);
typedef pcap_t *(*pcap_open_live_fn)(const char *, int, int, int, char *);
typedef int (*pcap_next_ex_fn)(pcap_t *, struct pcap_pkthdr **, const u_char **);
typedef int (*pcap_compile_fn)(pcap_t *, struct bpf_program *, const char *, int, bpf_u_int32);
typedef void (*pcap_close_fn)(pcap_t *);
typedef int (*pcap_setfilter_fn)(pcap_t *, struct bpf_program *);
typedef int (*pcap_sendpacket_fn)(pcap_t *, const u_char *, int);
typedef int (*pcap_set_datalink_fn)(pcap_t *, int);
typedef int (*pcap_dispatch_fn)(pcap_t *, int, pcap_handler, u_char *);
>>>>>>> upstream/master

class pcap_module : public osd_module, public netdev_module
{
public:
<<<<<<< HEAD

	pcap_module()
	: osd_module(OSD_NETDEV_PROVIDER, "pcap"), netdev_module(), handle(NULL)
	{
	}
	virtual ~pcap_module() { }

	virtual int init(const osd_options &options);
	virtual void exit();

	virtual bool probe();

	HMODULE handle;
};

static int (*pcap_compile_dl)(pcap_t *, struct bpf_program *, char *, int, bpf_u_int32) = NULL;
static int (*pcap_findalldevs_dl)(pcap_if_t **, char *) = NULL;
static pcap_t *(*pcap_open_live_dl)(const char *name, int, int, int, char *) = NULL;
static int (*pcap_next_ex_dl)(pcap_t *, struct pcap_pkthdr **, const u_char **) = NULL;
static void (*pcap_close_dl)(pcap_t *) = NULL;
static int (*pcap_setfilter_dl)(pcap_t *, struct bpf_program *) = NULL;
static int (*pcap_sendpacket_dl)(pcap_t *, u_char *, int) = NULL;
static int (*pcap_set_datalink_dl)(pcap_t *, int) = NULL;
static int (*pcap_dispatch_dl)(pcap_t *, int, pcap_handler callback, u_char *) = NULL;


#if 0
#define pcap_compile_dl pcap_compile
#define pcap_findalldevs_dl pcap_findalldevs
#define pcap_open_live_dl pcap_open_live
#define pcap_next_ex_dl pcap_next_ex
#define pcap_close_dl pcap_close
#define pcap_setfilter_dl pcap_setfilter
#define pcap_sendpacket_dl pcap_sendpacket
#define pcap_set_datalink_dl pcap_set_datalink
#endif

#ifdef SDLMAME_MACOSX
struct netdev_pcap_context {
	UINT8 *pkt;
	int len;
	pcap_t *p;

	UINT8 packets[32][1600];
=======
	pcap_module()
		: osd_module(OSD_NETDEV_PROVIDER, "pcap"), netdev_module(),
		  pcap_findalldevs_dl(nullptr), pcap_open_live_dl(nullptr), pcap_next_ex_dl(nullptr), pcap_compile_dl(nullptr),
		  pcap_close_dl(nullptr), pcap_setfilter_dl(nullptr), pcap_sendpacket_dl(nullptr), pcap_set_datalink_dl(nullptr), pcap_dispatch_dl(nullptr)
	{
	}

	virtual ~pcap_module() { }

	virtual int init(const osd_options &options) override;
	virtual void exit() override;

	virtual bool probe() override
	{
		pcap_dll = osd::dynamic_module::open({ LIB_NAME });

		pcap_findalldevs_dl = pcap_dll->bind<pcap_findalldevs_fn>("pcap_findalldevs");
		pcap_open_live_dl = pcap_dll->bind<pcap_open_live_fn>("pcap_open_live");
		pcap_next_ex_dl = pcap_dll->bind<pcap_next_ex_fn>("pcap_next_ex");
		pcap_compile_dl = pcap_dll->bind<pcap_compile_fn>("pcap_compile");
		pcap_close_dl = pcap_dll->bind<pcap_close_fn>("pcap_close");
		pcap_setfilter_dl = pcap_dll->bind<pcap_setfilter_fn>("pcap_setfilter");
		pcap_sendpacket_dl = pcap_dll->bind<pcap_sendpacket_fn>("pcap_sendpacket");
		pcap_set_datalink_dl = pcap_dll->bind<pcap_set_datalink_fn>("pcap_set_datalink");
		pcap_dispatch_dl = pcap_dll->bind<pcap_dispatch_fn>("pcap_dispatch");

		if (!pcap_findalldevs_dl || !pcap_open_live_dl    || !pcap_next_ex_dl   ||
			!pcap_compile_dl     || !pcap_close_dl        || !pcap_setfilter_dl ||
			!pcap_sendpacket_dl  || !pcap_set_datalink_dl || !pcap_dispatch_dl)
		{
			osd_printf_verbose("Unable to load the PCAP library\n");
			return false;
		}

		return true;
	}

	osd::dynamic_module::ptr pcap_dll;

	pcap_findalldevs_fn  pcap_findalldevs_dl;
	pcap_open_live_fn    pcap_open_live_dl;
	pcap_next_ex_fn      pcap_next_ex_dl;
	pcap_compile_fn      pcap_compile_dl;
	pcap_close_fn        pcap_close_dl;
	pcap_setfilter_fn    pcap_setfilter_dl;
	pcap_sendpacket_fn   pcap_sendpacket_dl;
	pcap_set_datalink_fn pcap_set_datalink_dl;
	pcap_dispatch_fn     pcap_dispatch_dl;
};

// FIXME: bridge between pcap_module and netdev_pcap
static pcap_module *module = nullptr;

#ifdef SDLMAME_MACOSX
struct netdev_pcap_context {
	uint8_t *pkt;
	int len;
	pcap_t *p;

	uint8_t packets[32][1600];
>>>>>>> upstream/master
	int packetlens[32];
	int head;
	int tail;
};
#endif

class netdev_pcap : public osd_netdev
{
public:
	netdev_pcap(const char *name, class device_network_interface *ifdev, int rate);
	~netdev_pcap();

<<<<<<< HEAD
	int send(UINT8 *buf, int len);
	void set_mac(const char *mac);
protected:
	int recv_dev(UINT8 **buf);
=======
	virtual int send(uint8_t *buf, int len) override;
	virtual void set_mac(const char *mac) override;
protected:
	virtual int recv_dev(uint8_t **buf) override;
>>>>>>> upstream/master
private:
	pcap_t *m_p;
#ifdef SDLMAME_MACOSX
	struct netdev_pcap_context m_ctx;
	pthread_t m_thread;
#endif
};

#ifdef SDLMAME_MACOSX
static void netdev_pcap_handler(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes) {
	struct netdev_pcap_context *ctx = (struct netdev_pcap_context*)user;

	if(!ctx->p) return;

	if(OSAtomicCompareAndSwapInt((ctx->head+1) & 0x1F, ctx->tail, &ctx->tail)) {
		printf("buffer full, dropping packet\n");
		return;
	}
	memcpy(ctx->packets[ctx->head], bytes, h->len);
	ctx->packetlens[ctx->head] = h->len;
	OSAtomicCompareAndSwapInt(ctx->head, (ctx->head+1) & 0x1F, &ctx->head);
}

static void *netdev_pcap_blocker(void *arg) {
	struct netdev_pcap_context *ctx = (struct netdev_pcap_context*)arg;

	while(ctx && ctx->p) {
<<<<<<< HEAD
		pcap_dispatch_dl(ctx->p, 1, netdev_pcap_handler, (u_char*)ctx);
=======
		(*module->pcap_dispatch_dl)(ctx->p, 1, netdev_pcap_handler, (u_char*)ctx);
>>>>>>> upstream/master
	}

	return 0;
}
#endif

netdev_pcap::netdev_pcap(const char *name, class device_network_interface *ifdev, int rate)
	: osd_netdev(ifdev, rate)
{
	char errbuf[PCAP_ERRBUF_SIZE];
#if defined(SDLMAME_WIN32) || defined(OSD_WINDOWS)
<<<<<<< HEAD
	m_p = pcap_open_live_dl(name, 65535, 1, -1, errbuf);
#else
	m_p = pcap_open_live_dl(name, 65535, 1, 1, errbuf);
=======
	m_p = (*module->pcap_open_live_dl)(name, 65535, 1, -1, errbuf);
#else
	m_p = (*module->pcap_open_live_dl)(name, 65535, 1, 1, errbuf);
>>>>>>> upstream/master
#endif
	if(!m_p)
	{
		osd_printf_error("Unable to open %s: %s\n", name, errbuf);
		return;
	}
<<<<<<< HEAD
	if(pcap_set_datalink_dl(m_p, DLT_EN10MB) == -1)
	{
		osd_printf_error("Unable to set %s to ethernet", name);
		pcap_close_dl(m_p);
		m_p = NULL;
=======
	if ((*module->pcap_set_datalink_dl)(m_p, DLT_EN10MB) == -1)
	{
		osd_printf_error("Unable to set %s to ethernet", name);
		(*module->pcap_close_dl)(m_p);
		m_p = nullptr;
>>>>>>> upstream/master
		return;
	}
	netdev_pcap::set_mac(get_mac());

#ifdef SDLMAME_MACOSX
	m_ctx.head = 0;
	m_ctx.tail = 0;
	m_ctx.p = m_p;
<<<<<<< HEAD
	pthread_create(&m_thread, NULL, netdev_pcap_blocker, &m_ctx);
=======
	pthread_create(&m_thread, nullptr, netdev_pcap_blocker, &m_ctx);
>>>>>>> upstream/master
#endif
}

void netdev_pcap::set_mac(const char *mac)
{
	char filter[256];
	struct bpf_program fp;
	if(!m_p) return;
#ifdef SDLMAME_MACOSX
	sprintf(filter, "not ether src %.2X:%.2X:%.2X:%.2X:%.2X:%.2X and (ether dst %.2X:%.2X:%.2X:%.2X:%.2X:%.2X or ether multicast or ether broadcast or ether dst 09:00:07:ff:ff:ff)", (unsigned char)mac[0], (unsigned char)mac[1], (unsigned char)mac[2],(unsigned char)mac[3], (unsigned char)mac[4], (unsigned char)mac[5], (unsigned char)mac[0], (unsigned char)mac[1], (unsigned char)mac[2],(unsigned char)mac[3], (unsigned char)mac[4], (unsigned char)mac[5]);
#else
	sprintf(filter, "ether dst %.2X:%.2X:%.2X:%.2X:%.2X:%.2X or ether multicast or ether broadcast", (unsigned char)mac[0], (unsigned char)mac[1], (unsigned char)mac[2],(unsigned char)mac[3], (unsigned char)mac[4], (unsigned char)mac[5]);
#endif
<<<<<<< HEAD
	if(pcap_compile_dl(m_p, &fp, filter, 1, 0) == -1) {
		osd_printf_error("Error with pcap_compile\n");
	}
	if(pcap_setfilter_dl(m_p, &fp) == -1) {
=======
	if ((*module->pcap_compile_dl)(m_p, &fp, filter, 1, 0) == -1) {
		osd_printf_error("Error with pcap_compile\n");
	}
	if ((*module->pcap_setfilter_dl)(m_p, &fp) == -1) {
>>>>>>> upstream/master
		osd_printf_error("Error with pcap_setfilter\n");
	}
}

<<<<<<< HEAD
int netdev_pcap::send(UINT8 *buf, int len)
=======
int netdev_pcap::send(uint8_t *buf, int len)
>>>>>>> upstream/master
{
	int ret;
	if(!m_p) {
		printf("send invoked, but no pcap context\n");
		return 0;
	}
<<<<<<< HEAD
	ret = pcap_sendpacket_dl(m_p, buf, len);
=======
	ret = (*module->pcap_sendpacket_dl)(m_p, buf, len);
>>>>>>> upstream/master
	printf("sent packet length %d, returned %d\n", len, ret);
	return ret ? len : 0;
	//return (!pcap_sendpacket_dl(m_p, buf, len))?len:0;
}

<<<<<<< HEAD
int netdev_pcap::recv_dev(UINT8 **buf)
{
#ifdef SDLMAME_MACOSX
	UINT8 pktbuf[2048];
=======
int netdev_pcap::recv_dev(uint8_t **buf)
{
#ifdef SDLMAME_MACOSX
	uint8_t pktbuf[2048];
>>>>>>> upstream/master
	int ret;

	// Empty
	if(OSAtomicCompareAndSwapInt(m_ctx.head, m_ctx.tail, &m_ctx.tail)) {
		return 0;
	}

	memcpy(pktbuf, m_ctx.packets[m_ctx.tail], m_ctx.packetlens[m_ctx.tail]);
	ret = m_ctx.packetlens[m_ctx.tail];
	OSAtomicCompareAndSwapInt(m_ctx.tail, (m_ctx.tail+1) & 0x1F, &m_ctx.tail);
	*buf = pktbuf;
	return ret;
#else
	struct pcap_pkthdr *header;
	if(!m_p) return 0;
<<<<<<< HEAD
	return (pcap_next_ex_dl(m_p, &header, (const u_char **)buf) == 1)?header->len:0;
=======
	return ((*module->pcap_next_ex_dl)(m_p, &header, (const u_char **)buf) == 1)?header->len:0;
>>>>>>> upstream/master
#endif
}

netdev_pcap::~netdev_pcap()
{
#ifdef SDLMAME_MACOSX
<<<<<<< HEAD
	m_ctx.p = NULL;
	pthread_cancel(m_thread);
	pthread_join(m_thread, NULL);
#endif
	if(m_p) pcap_close_dl(m_p);
	m_p = NULL;
=======
	m_ctx.p = nullptr;
	pthread_cancel(m_thread);
	pthread_join(m_thread, nullptr);
#endif
	if(m_p) (*module->pcap_close_dl)(m_p);
	m_p = nullptr;
>>>>>>> upstream/master
}

static CREATE_NETDEV(create_pcap)
{
	class netdev_pcap *dev = global_alloc(netdev_pcap(ifname, ifdev, rate));
	return dynamic_cast<osd_netdev *>(dev);
}

<<<<<<< HEAD
bool pcap_module::probe()
{
	if (handle == NULL)
	{
		handle = LoadDynamicLibrary(LIB_NAME);
		return (handle != NULL);
	}
	return true;
}


=======
>>>>>>> upstream/master
int pcap_module::init(const osd_options &options)
{
	pcap_if_t *devs;
	char errbuf[PCAP_ERRBUF_SIZE];

<<<<<<< HEAD
	try
	{
		if(!(pcap_findalldevs_dl = (int (*)(pcap_if_t **, char *))GetProcAddress(handle, "pcap_findalldevs")))
			throw GetLastError();
		if(!(pcap_open_live_dl = (pcap_t* (*)(const char *, int, int, int, char *))GetProcAddress(handle, "pcap_open_live")))
			throw GetLastError();
		if(!(pcap_next_ex_dl = (int (*)(pcap_t *, struct pcap_pkthdr **, const u_char **))GetProcAddress(handle, "pcap_next_ex")))
			throw GetLastError();
		if(!(pcap_compile_dl = (int (*)(pcap_t *, struct bpf_program *, char *, int, bpf_u_int32))GetProcAddress(handle, "pcap_compile")))
			throw GetLastError();
		if(!(pcap_close_dl = (void (*)(pcap_t *))GetProcAddress(handle, "pcap_close")))
			throw GetLastError();
		if(!(pcap_setfilter_dl = (int (*)(pcap_t *, struct bpf_program *))GetProcAddress(handle, "pcap_setfilter")))
			throw GetLastError();
		if(!(pcap_sendpacket_dl = (int (*)(pcap_t *, u_char *, int))GetProcAddress(handle, "pcap_sendpacket")))
			throw GetLastError();
		if(!(pcap_set_datalink_dl = (int (*)(pcap_t *, int))GetProcAddress(handle, "pcap_set_datalink")))
			throw GetLastError();
		if(!(pcap_dispatch_dl = (int (*)(pcap_t *, int, pcap_handler callback, u_char *))GetProcAddress(handle, "pcap_dispatch")))
			throw GetLastError();
	}
	catch (except_type e)
	{
		FreeLibrary(handle);
		osd_printf_error(LIB_ERROR_STR, e);
		return 1;
	}
	if(pcap_findalldevs_dl(&devs, errbuf) == -1)
	{
		FreeLibrary(handle);
=======
	// FIXME: bridge between pcap_module and netdev_pcap
	module = this;

	if ((*pcap_findalldevs_dl)(&devs, errbuf) == -1)
	{
>>>>>>> upstream/master
		osd_printf_error("Unable to get network devices: %s\n", errbuf);
		return 1;
	}

	while(devs)
	{
		if(devs->description) {
			add_netdev(devs->name, devs->description, create_pcap);
		} else {
			add_netdev(devs->name, devs->name, create_pcap);
		}
		devs = devs->next;
	}
	return 0;
}

void pcap_module::exit()
{
	clear_netdev();
<<<<<<< HEAD
	FreeLibrary(handle);
	handle = NULL;
}
=======
}

>>>>>>> upstream/master
#else
	#include "modules/osdmodule.h"
	#include "netdev_module.h"

	MODULE_NOT_SUPPORTED(pcap_module, OSD_NETDEV_PROVIDER, "pcap")
#endif


MODULE_DEFINITION(NETDEV_PCAP, pcap_module)
