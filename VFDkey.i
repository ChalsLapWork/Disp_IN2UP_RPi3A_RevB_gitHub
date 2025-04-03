# 0 "VFDkey.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "VFDkey.c"
# 1 "VFDkey.h" 1

void PortaliniciokeyUP(void);
void PortaliniciokeyRT(void);
void PortaliniciokeyLF(void);
void PortaliniciokeyDN(void);
void PortaliniciokeyEN(void);

void MenuInsightkeyUP(void);
void MenuInsightkeyRT(void);
void MenuInsightkeyLF(void);
void MenuInsightkeyDN(void);
void MenuInsightkeyEN(void);

void AjusteProductokeyUP(void);
void AjusteProductokeyRT(void);
void AjusteProductokeyLF(void);
void AjusteProductokeyDN(void);
void AjusteProductokeyEN(void);

void AjusteParamProdkeyUP(void);
void AjusteParamProdkeyRT(void);
void AjusteParamProdkeyLF(void);
void AjusteParamProdkeyDN(void);
void AjusteParamProdkeyEN(void);

void AjustedeSistemakeyUP(void);
void AjustedeSistemakeyRT(void);
void AjustedeSistemakeyLF(void);
void AjustedeSistemakeyDN(void);
void AjustedeSistemakeyEN(void);

void PANTALLA_DDSkeyUP(void);
void PANTALLA_DDSkeyRT(void);
void PANTALLA_DDSkeyLF(void);
void PANTALLA_DDSkeyDN(void);
void PANTALLA_DDSkeyEN(void);

void MenuInformacionUsuariokeyUP(void);
void MenuInformacionUsuariokeyRT(void);
void MenuInformacionUsuariokeyLF(void);
void MenuInformacionUsuariokeyDN(void);
void MenuInformacionUsuariokeyEN(void);


void operacionVariable(unsigned char posx,unsigned short int y,unsigned char igxm0,unsigned char op);
unsigned char procSensxDigitoRT(unsigned char posx,unsigned char posy,unsigned short int *Sens);
# 2 "VFDkey.c" 2
# 1 "VFDmenu.h" 1
# 20 "VFDmenu.h"
# 1 "queue.h" 1



# 1 "/usr/lib/gcc/aarch64-linux-gnu/12/include/stdint.h" 1 3 4
# 9 "/usr/lib/gcc/aarch64-linux-gnu/12/include/stdint.h" 3 4
# 1 "/usr/include/stdint.h" 1 3 4
# 26 "/usr/include/stdint.h" 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/libc-header-start.h" 1 3 4
# 33 "/usr/include/aarch64-linux-gnu/bits/libc-header-start.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 392 "/usr/include/features.h" 3 4
# 1 "/usr/include/features-time64.h" 1 3 4
# 20 "/usr/include/features-time64.h" 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/wordsize.h" 1 3 4
# 21 "/usr/include/features-time64.h" 2 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/timesize.h" 1 3 4
# 22 "/usr/include/features-time64.h" 2 3 4
# 393 "/usr/include/features.h" 2 3 4
# 489 "/usr/include/features.h" 3 4
# 1 "/usr/include/aarch64-linux-gnu/sys/cdefs.h" 1 3 4
# 561 "/usr/include/aarch64-linux-gnu/sys/cdefs.h" 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/wordsize.h" 1 3 4
# 562 "/usr/include/aarch64-linux-gnu/sys/cdefs.h" 2 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/long-double.h" 1 3 4
# 563 "/usr/include/aarch64-linux-gnu/sys/cdefs.h" 2 3 4
# 490 "/usr/include/features.h" 2 3 4
# 513 "/usr/include/features.h" 3 4
# 1 "/usr/include/aarch64-linux-gnu/gnu/stubs.h" 1 3 4




# 1 "/usr/include/aarch64-linux-gnu/bits/wordsize.h" 1 3 4
# 6 "/usr/include/aarch64-linux-gnu/gnu/stubs.h" 2 3 4


# 1 "/usr/include/aarch64-linux-gnu/gnu/stubs-lp64.h" 1 3 4
# 9 "/usr/include/aarch64-linux-gnu/gnu/stubs.h" 2 3 4
# 514 "/usr/include/features.h" 2 3 4
# 34 "/usr/include/aarch64-linux-gnu/bits/libc-header-start.h" 2 3 4
# 27 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/types.h" 1 3 4
# 27 "/usr/include/aarch64-linux-gnu/bits/types.h" 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/wordsize.h" 1 3 4
# 28 "/usr/include/aarch64-linux-gnu/bits/types.h" 2 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/timesize.h" 1 3 4
# 29 "/usr/include/aarch64-linux-gnu/bits/types.h" 2 3 4



# 31 "/usr/include/aarch64-linux-gnu/bits/types.h" 3 4
typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;






typedef __int8_t __int_least8_t;
typedef __uint8_t __uint_least8_t;
typedef __int16_t __int_least16_t;
typedef __uint16_t __uint_least16_t;
typedef __int32_t __int_least32_t;
typedef __uint32_t __uint_least32_t;
typedef __int64_t __int_least64_t;
typedef __uint64_t __uint_least64_t;



typedef long int __quad_t;
typedef unsigned long int __u_quad_t;







typedef long int __intmax_t;
typedef unsigned long int __uintmax_t;
# 141 "/usr/include/aarch64-linux-gnu/bits/types.h" 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/typesizes.h" 1 3 4
# 142 "/usr/include/aarch64-linux-gnu/bits/types.h" 2 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/time64.h" 1 3 4
# 143 "/usr/include/aarch64-linux-gnu/bits/types.h" 2 3 4


typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;
typedef long int __suseconds64_t;

typedef int __daddr_t;
typedef int __key_t;


typedef int __clockid_t;


typedef void * __timer_t;


typedef int __blksize_t;




typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;


typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;


typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;


typedef long int __fsword_t;

typedef long int __ssize_t;


typedef long int __syscall_slong_t;

typedef unsigned long int __syscall_ulong_t;



typedef __off64_t __loff_t;
typedef char *__caddr_t;


typedef long int __intptr_t;


typedef unsigned int __socklen_t;




typedef int __sig_atomic_t;
# 28 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/wchar.h" 1 3 4
# 29 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/wordsize.h" 1 3 4
# 30 "/usr/include/stdint.h" 2 3 4




# 1 "/usr/include/aarch64-linux-gnu/bits/stdint-intn.h" 1 3 4
# 24 "/usr/include/aarch64-linux-gnu/bits/stdint-intn.h" 3 4
typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
typedef __int64_t int64_t;
# 35 "/usr/include/stdint.h" 2 3 4


# 1 "/usr/include/aarch64-linux-gnu/bits/stdint-uintn.h" 1 3 4
# 24 "/usr/include/aarch64-linux-gnu/bits/stdint-uintn.h" 3 4
typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __uint64_t uint64_t;
# 38 "/usr/include/stdint.h" 2 3 4





typedef __int_least8_t int_least8_t;
typedef __int_least16_t int_least16_t;
typedef __int_least32_t int_least32_t;
typedef __int_least64_t int_least64_t;


typedef __uint_least8_t uint_least8_t;
typedef __uint_least16_t uint_least16_t;
typedef __uint_least32_t uint_least32_t;
typedef __uint_least64_t uint_least64_t;





typedef signed char int_fast8_t;

typedef long int int_fast16_t;
typedef long int int_fast32_t;
typedef long int int_fast64_t;
# 71 "/usr/include/stdint.h" 3 4
typedef unsigned char uint_fast8_t;

typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long int uint_fast64_t;
# 87 "/usr/include/stdint.h" 3 4
typedef long int intptr_t;


typedef unsigned long int uintptr_t;
# 101 "/usr/include/stdint.h" 3 4
typedef __intmax_t intmax_t;
typedef __uintmax_t uintmax_t;
# 10 "/usr/lib/gcc/aarch64-linux-gnu/12/include/stdint.h" 2 3 4
# 5 "queue.h" 2



# 1 "/usr/include/pthread.h" 1 3 4
# 22 "/usr/include/pthread.h" 3 4
# 1 "/usr/include/sched.h" 1 3 4
# 29 "/usr/include/sched.h" 3 4
# 1 "/usr/lib/gcc/aarch64-linux-gnu/12/include/stddef.h" 1 3 4
# 214 "/usr/lib/gcc/aarch64-linux-gnu/12/include/stddef.h" 3 4
typedef long unsigned int size_t;
# 30 "/usr/include/sched.h" 2 3 4

# 1 "/usr/include/aarch64-linux-gnu/bits/types/time_t.h" 1 3 4
# 10 "/usr/include/aarch64-linux-gnu/bits/types/time_t.h" 3 4
typedef __time_t time_t;
# 32 "/usr/include/sched.h" 2 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/types/struct_timespec.h" 1 3 4





# 1 "/usr/include/aarch64-linux-gnu/bits/endian.h" 1 3 4
# 35 "/usr/include/aarch64-linux-gnu/bits/endian.h" 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/endianness.h" 1 3 4
# 36 "/usr/include/aarch64-linux-gnu/bits/endian.h" 2 3 4
# 7 "/usr/include/aarch64-linux-gnu/bits/types/struct_timespec.h" 2 3 4




struct timespec
{



  __time_t tv_sec;




  __syscall_slong_t tv_nsec;
# 31 "/usr/include/aarch64-linux-gnu/bits/types/struct_timespec.h" 3 4
};
# 33 "/usr/include/sched.h" 2 3 4





typedef __pid_t pid_t;




# 1 "/usr/include/aarch64-linux-gnu/bits/sched.h" 1 3 4
# 80 "/usr/include/aarch64-linux-gnu/bits/sched.h" 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/types/struct_sched_param.h" 1 3 4
# 23 "/usr/include/aarch64-linux-gnu/bits/types/struct_sched_param.h" 3 4
struct sched_param
{
  int sched_priority;
};
# 81 "/usr/include/aarch64-linux-gnu/bits/sched.h" 2 3 4


# 102 "/usr/include/aarch64-linux-gnu/bits/sched.h" 3 4

# 44 "/usr/include/sched.h" 2 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/cpu-set.h" 1 3 4
# 32 "/usr/include/aarch64-linux-gnu/bits/cpu-set.h" 3 4
typedef unsigned long int __cpu_mask;






typedef struct
{
  __cpu_mask __bits[1024 / (8 * sizeof (__cpu_mask))];
} cpu_set_t;
# 115 "/usr/include/aarch64-linux-gnu/bits/cpu-set.h" 3 4


extern int __sched_cpucount (size_t __setsize, const cpu_set_t *__setp)
     __attribute__ ((__nothrow__ , __leaf__));
extern cpu_set_t *__sched_cpualloc (size_t __count) __attribute__ ((__nothrow__ , __leaf__)) ;
extern void __sched_cpufree (cpu_set_t *__set) __attribute__ ((__nothrow__ , __leaf__));


# 45 "/usr/include/sched.h" 2 3 4









extern int sched_setparam (__pid_t __pid, const struct sched_param *__param)
     __attribute__ ((__nothrow__ , __leaf__));


extern int sched_getparam (__pid_t __pid, struct sched_param *__param) __attribute__ ((__nothrow__ , __leaf__));


extern int sched_setscheduler (__pid_t __pid, int __policy,
          const struct sched_param *__param) __attribute__ ((__nothrow__ , __leaf__));


extern int sched_getscheduler (__pid_t __pid) __attribute__ ((__nothrow__ , __leaf__));


extern int sched_yield (void) __attribute__ ((__nothrow__ , __leaf__));


extern int sched_get_priority_max (int __algorithm) __attribute__ ((__nothrow__ , __leaf__));


extern int sched_get_priority_min (int __algorithm) __attribute__ ((__nothrow__ , __leaf__));



extern int sched_rr_get_interval (__pid_t __pid, struct timespec *__t) __attribute__ ((__nothrow__ , __leaf__));
# 138 "/usr/include/sched.h" 3 4

# 23 "/usr/include/pthread.h" 2 3 4
# 1 "/usr/include/time.h" 1 3 4
# 29 "/usr/include/time.h" 3 4
# 1 "/usr/lib/gcc/aarch64-linux-gnu/12/include/stddef.h" 1 3 4
# 30 "/usr/include/time.h" 2 3 4



# 1 "/usr/include/aarch64-linux-gnu/bits/time.h" 1 3 4
# 34 "/usr/include/time.h" 2 3 4



# 1 "/usr/include/aarch64-linux-gnu/bits/types/clock_t.h" 1 3 4






typedef __clock_t clock_t;
# 38 "/usr/include/time.h" 2 3 4

# 1 "/usr/include/aarch64-linux-gnu/bits/types/struct_tm.h" 1 3 4






struct tm
{
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;


  long int tm_gmtoff;
  const char *tm_zone;




};
# 40 "/usr/include/time.h" 2 3 4






# 1 "/usr/include/aarch64-linux-gnu/bits/types/clockid_t.h" 1 3 4






typedef __clockid_t clockid_t;
# 47 "/usr/include/time.h" 2 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/types/timer_t.h" 1 3 4






typedef __timer_t timer_t;
# 48 "/usr/include/time.h" 2 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/types/struct_itimerspec.h" 1 3 4







struct itimerspec
  {
    struct timespec it_interval;
    struct timespec it_value;
  };
# 49 "/usr/include/time.h" 2 3 4
struct sigevent;
# 60 "/usr/include/time.h" 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/types/locale_t.h" 1 3 4
# 22 "/usr/include/aarch64-linux-gnu/bits/types/locale_t.h" 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/types/__locale_t.h" 1 3 4
# 27 "/usr/include/aarch64-linux-gnu/bits/types/__locale_t.h" 3 4
struct __locale_struct
{

  struct __locale_data *__locales[13];


  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;


  const char *__names[13];
};

typedef struct __locale_struct *__locale_t;
# 23 "/usr/include/aarch64-linux-gnu/bits/types/locale_t.h" 2 3 4

typedef __locale_t locale_t;
# 61 "/usr/include/time.h" 2 3 4











extern clock_t clock (void) __attribute__ ((__nothrow__ , __leaf__));



extern time_t time (time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));


extern double difftime (time_t __time1, time_t __time0)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern time_t mktime (struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));
# 100 "/usr/include/time.h" 3 4
extern size_t strftime (char *__restrict __s, size_t __maxsize,
   const char *__restrict __format,
   const struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));
# 116 "/usr/include/time.h" 3 4
extern size_t strftime_l (char *__restrict __s, size_t __maxsize,
     const char *__restrict __format,
     const struct tm *__restrict __tp,
     locale_t __loc) __attribute__ ((__nothrow__ , __leaf__));
# 132 "/usr/include/time.h" 3 4
extern struct tm *gmtime (const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));



extern struct tm *localtime (const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));
# 154 "/usr/include/time.h" 3 4
extern struct tm *gmtime_r (const time_t *__restrict __timer,
       struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));



extern struct tm *localtime_r (const time_t *__restrict __timer,
          struct tm *__restrict __tp) __attribute__ ((__nothrow__ , __leaf__));
# 179 "/usr/include/time.h" 3 4
extern char *asctime (const struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));



extern char *ctime (const time_t *__timer) __attribute__ ((__nothrow__ , __leaf__));
# 197 "/usr/include/time.h" 3 4
extern char *asctime_r (const struct tm *__restrict __tp,
   char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));



extern char *ctime_r (const time_t *__restrict __timer,
        char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));
# 217 "/usr/include/time.h" 3 4
extern char *__tzname[2];
extern int __daylight;
extern long int __timezone;




extern char *tzname[2];



extern void tzset (void) __attribute__ ((__nothrow__ , __leaf__));



extern int daylight;
extern long int timezone;
# 246 "/usr/include/time.h" 3 4
extern time_t timegm (struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));
# 263 "/usr/include/time.h" 3 4
extern time_t timelocal (struct tm *__tp) __attribute__ ((__nothrow__ , __leaf__));







extern int dysize (int __year) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
# 281 "/usr/include/time.h" 3 4
extern int nanosleep (const struct timespec *__requested_time,
        struct timespec *__remaining);


extern int clock_getres (clockid_t __clock_id, struct timespec *__res) __attribute__ ((__nothrow__ , __leaf__));


extern int clock_gettime (clockid_t __clock_id, struct timespec *__tp)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));


extern int clock_settime (clockid_t __clock_id, const struct timespec *__tp)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
# 323 "/usr/include/time.h" 3 4
extern int clock_nanosleep (clockid_t __clock_id, int __flags,
       const struct timespec *__req,
       struct timespec *__rem);
# 338 "/usr/include/time.h" 3 4
extern int clock_getcpuclockid (pid_t __pid, clockid_t *__clock_id) __attribute__ ((__nothrow__ , __leaf__));




extern int timer_create (clockid_t __clock_id,
    struct sigevent *__restrict __evp,
    timer_t *__restrict __timerid) __attribute__ ((__nothrow__ , __leaf__));


extern int timer_delete (timer_t __timerid) __attribute__ ((__nothrow__ , __leaf__));



extern int timer_settime (timer_t __timerid, int __flags,
     const struct itimerspec *__restrict __value,
     struct itimerspec *__restrict __ovalue) __attribute__ ((__nothrow__ , __leaf__));


extern int timer_gettime (timer_t __timerid, struct itimerspec *__value)
     __attribute__ ((__nothrow__ , __leaf__));
# 376 "/usr/include/time.h" 3 4
extern int timer_getoverrun (timer_t __timerid) __attribute__ ((__nothrow__ , __leaf__));






extern int timespec_get (struct timespec *__ts, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 452 "/usr/include/time.h" 3 4

# 24 "/usr/include/pthread.h" 2 3 4


# 1 "/usr/include/aarch64-linux-gnu/bits/pthreadtypes.h" 1 3 4
# 23 "/usr/include/aarch64-linux-gnu/bits/pthreadtypes.h" 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/thread-shared-types.h" 1 3 4
# 44 "/usr/include/aarch64-linux-gnu/bits/thread-shared-types.h" 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/pthreadtypes-arch.h" 1 3 4
# 45 "/usr/include/aarch64-linux-gnu/bits/thread-shared-types.h" 2 3 4

# 1 "/usr/include/aarch64-linux-gnu/bits/atomic_wide_counter.h" 1 3 4
# 25 "/usr/include/aarch64-linux-gnu/bits/atomic_wide_counter.h" 3 4
typedef union
{
  __extension__ unsigned long long int __value64;
  struct
  {
    unsigned int __low;
    unsigned int __high;
  } __value32;
} __atomic_wide_counter;
# 47 "/usr/include/aarch64-linux-gnu/bits/thread-shared-types.h" 2 3 4




typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;

typedef struct __pthread_internal_slist
{
  struct __pthread_internal_slist *__next;
} __pthread_slist_t;
# 76 "/usr/include/aarch64-linux-gnu/bits/thread-shared-types.h" 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/struct_mutex.h" 1 3 4
# 27 "/usr/include/aarch64-linux-gnu/bits/struct_mutex.h" 3 4
struct __pthread_mutex_s
{
  int __lock ;
  unsigned int __count;
  int __owner;

  unsigned int __nusers;
# 58 "/usr/include/aarch64-linux-gnu/bits/struct_mutex.h" 3 4
  int __kind;




  int __spins;
  __pthread_list_t __list;
# 74 "/usr/include/aarch64-linux-gnu/bits/struct_mutex.h" 3 4
};
# 77 "/usr/include/aarch64-linux-gnu/bits/thread-shared-types.h" 2 3 4
# 89 "/usr/include/aarch64-linux-gnu/bits/thread-shared-types.h" 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/struct_rwlock.h" 1 3 4
# 23 "/usr/include/aarch64-linux-gnu/bits/struct_rwlock.h" 3 4
struct __pthread_rwlock_arch_t
{
  unsigned int __readers;
  unsigned int __writers;
  unsigned int __wrphase_futex;
  unsigned int __writers_futex;
  unsigned int __pad3;
  unsigned int __pad4;
  int __cur_writer;
  int __shared;
  unsigned long int __pad1;
  unsigned long int __pad2;
  unsigned int __flags;
};
# 90 "/usr/include/aarch64-linux-gnu/bits/thread-shared-types.h" 2 3 4




struct __pthread_cond_s
{
  __atomic_wide_counter __wseq;
  __atomic_wide_counter __g1_start;
  unsigned int __g_refs[2] ;
  unsigned int __g_size[2];
  unsigned int __g1_orig_size;
  unsigned int __wrefs;
  unsigned int __g_signals[2];
};

typedef unsigned int __tss_t;
typedef unsigned long int __thrd_t;

typedef struct
{
  int __data ;
} __once_flag;
# 24 "/usr/include/aarch64-linux-gnu/bits/pthreadtypes.h" 2 3 4



typedef unsigned long int pthread_t;




typedef union
{
  char __size[8];
  int __align;
} pthread_mutexattr_t;




typedef union
{
  char __size[8];
  int __align;
} pthread_condattr_t;



typedef unsigned int pthread_key_t;



typedef int pthread_once_t;


union pthread_attr_t
{
  char __size[64];
  long int __align;
};

typedef union pthread_attr_t pthread_attr_t;




typedef union
{
  struct __pthread_mutex_s __data;
  char __size[48];
  long int __align;
} pthread_mutex_t;


typedef union
{
  struct __pthread_cond_s __data;
  char __size[48];
  __extension__ long long int __align;
} pthread_cond_t;





typedef union
{
  struct __pthread_rwlock_arch_t __data;
  char __size[56];
  long int __align;
} pthread_rwlock_t;

typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;





typedef volatile int pthread_spinlock_t;




typedef union
{
  char __size[32];
  long int __align;
} pthread_barrier_t;

typedef union
{
  char __size[8];
  int __align;
} pthread_barrierattr_t;
# 27 "/usr/include/pthread.h" 2 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/setjmp.h" 1 3 4
# 30 "/usr/include/aarch64-linux-gnu/bits/setjmp.h" 3 4
__extension__ typedef unsigned long long __jmp_buf [22];
# 28 "/usr/include/pthread.h" 2 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/wordsize.h" 1 3 4
# 29 "/usr/include/pthread.h" 2 3 4

# 1 "/usr/include/aarch64-linux-gnu/bits/types/__sigset_t.h" 1 3 4




typedef struct
{
  unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
} __sigset_t;
# 31 "/usr/include/pthread.h" 2 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/types/struct___jmp_buf_tag.h" 1 3 4
# 26 "/usr/include/aarch64-linux-gnu/bits/types/struct___jmp_buf_tag.h" 3 4
struct __jmp_buf_tag
  {




    __jmp_buf __jmpbuf;
    int __mask_was_saved;
    __sigset_t __saved_mask;
  };
# 32 "/usr/include/pthread.h" 2 3 4

# 1 "/usr/include/aarch64-linux-gnu/bits/pthread_stack_min-dynamic.h" 1 3 4
# 29 "/usr/include/aarch64-linux-gnu/bits/pthread_stack_min-dynamic.h" 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/pthread_stack_min.h" 1 3 4
# 30 "/usr/include/aarch64-linux-gnu/bits/pthread_stack_min-dynamic.h" 2 3 4
# 34 "/usr/include/pthread.h" 2 3 4



enum
{
  PTHREAD_CREATE_JOINABLE,

  PTHREAD_CREATE_DETACHED

};



enum
{
  PTHREAD_MUTEX_TIMED_NP,
  PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_ADAPTIVE_NP

  ,
  PTHREAD_MUTEX_NORMAL = PTHREAD_MUTEX_TIMED_NP,
  PTHREAD_MUTEX_RECURSIVE = PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK = PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_DEFAULT = PTHREAD_MUTEX_NORMAL





};




enum
{
  PTHREAD_MUTEX_STALLED,
  PTHREAD_MUTEX_STALLED_NP = PTHREAD_MUTEX_STALLED,
  PTHREAD_MUTEX_ROBUST,
  PTHREAD_MUTEX_ROBUST_NP = PTHREAD_MUTEX_ROBUST
};





enum
{
  PTHREAD_PRIO_NONE,
  PTHREAD_PRIO_INHERIT,
  PTHREAD_PRIO_PROTECT
};
# 104 "/usr/include/pthread.h" 3 4
enum
{
  PTHREAD_RWLOCK_PREFER_READER_NP,
  PTHREAD_RWLOCK_PREFER_WRITER_NP,
  PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP,
  PTHREAD_RWLOCK_DEFAULT_NP = PTHREAD_RWLOCK_PREFER_READER_NP
};
# 124 "/usr/include/pthread.h" 3 4
enum
{
  PTHREAD_INHERIT_SCHED,

  PTHREAD_EXPLICIT_SCHED

};



enum
{
  PTHREAD_SCOPE_SYSTEM,

  PTHREAD_SCOPE_PROCESS

};



enum
{
  PTHREAD_PROCESS_PRIVATE,

  PTHREAD_PROCESS_SHARED

};
# 159 "/usr/include/pthread.h" 3 4
struct _pthread_cleanup_buffer
{
  void (*__routine) (void *);
  void *__arg;
  int __canceltype;
  struct _pthread_cleanup_buffer *__prev;
};


enum
{
  PTHREAD_CANCEL_ENABLE,

  PTHREAD_CANCEL_DISABLE

};
enum
{
  PTHREAD_CANCEL_DEFERRED,

  PTHREAD_CANCEL_ASYNCHRONOUS

};
# 197 "/usr/include/pthread.h" 3 4





extern int pthread_create (pthread_t *__restrict __newthread,
      const pthread_attr_t *__restrict __attr,
      void *(*__start_routine) (void *),
      void *__restrict __arg) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 3)));





extern void pthread_exit (void *__retval) __attribute__ ((__noreturn__));







extern int pthread_join (pthread_t __th, void **__thread_return);
# 269 "/usr/include/pthread.h" 3 4
extern int pthread_detach (pthread_t __th) __attribute__ ((__nothrow__ , __leaf__));



extern pthread_t pthread_self (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int pthread_equal (pthread_t __thread1, pthread_t __thread2)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));







extern int pthread_attr_init (pthread_attr_t *__attr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_attr_destroy (pthread_attr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_attr_getdetachstate (const pthread_attr_t *__attr,
     int *__detachstate)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setdetachstate (pthread_attr_t *__attr,
     int __detachstate)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_attr_getguardsize (const pthread_attr_t *__attr,
          size_t *__guardsize)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setguardsize (pthread_attr_t *__attr,
          size_t __guardsize)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_attr_getschedparam (const pthread_attr_t *__restrict __attr,
           struct sched_param *__restrict __param)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setschedparam (pthread_attr_t *__restrict __attr,
           const struct sched_param *__restrict
           __param) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_getschedpolicy (const pthread_attr_t *__restrict
     __attr, int *__restrict __policy)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setschedpolicy (pthread_attr_t *__attr, int __policy)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_attr_getinheritsched (const pthread_attr_t *__restrict
      __attr, int *__restrict __inherit)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setinheritsched (pthread_attr_t *__attr,
      int __inherit)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_attr_getscope (const pthread_attr_t *__restrict __attr,
      int *__restrict __scope)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_attr_setscope (pthread_attr_t *__attr, int __scope)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_attr_getstackaddr (const pthread_attr_t *__restrict
          __attr, void **__restrict __stackaddr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) __attribute__ ((__deprecated__));





extern int pthread_attr_setstackaddr (pthread_attr_t *__attr,
          void *__stackaddr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__deprecated__));


extern int pthread_attr_getstacksize (const pthread_attr_t *__restrict
          __attr, size_t *__restrict __stacksize)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern int pthread_attr_setstacksize (pthread_attr_t *__attr,
          size_t __stacksize)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_attr_getstack (const pthread_attr_t *__restrict __attr,
      void **__restrict __stackaddr,
      size_t *__restrict __stacksize)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2, 3)));




extern int pthread_attr_setstack (pthread_attr_t *__attr, void *__stackaddr,
      size_t __stacksize) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 441 "/usr/include/pthread.h" 3 4
extern int pthread_setschedparam (pthread_t __target_thread, int __policy,
      const struct sched_param *__param)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3)));


extern int pthread_getschedparam (pthread_t __target_thread,
      int *__restrict __policy,
      struct sched_param *__restrict __param)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));


extern int pthread_setschedprio (pthread_t __target_thread, int __prio)
     __attribute__ ((__nothrow__ , __leaf__));
# 509 "/usr/include/pthread.h" 3 4
extern int pthread_once (pthread_once_t *__once_control,
    void (*__init_routine) (void)) __attribute__ ((__nonnull__ (1, 2)));
# 521 "/usr/include/pthread.h" 3 4
extern int pthread_setcancelstate (int __state, int *__oldstate);



extern int pthread_setcanceltype (int __type, int *__oldtype);


extern int pthread_cancel (pthread_t __th);




extern void pthread_testcancel (void);




struct __cancel_jmp_buf_tag
{
  __jmp_buf __cancel_jmp_buf;
  int __mask_was_saved;
};

typedef struct
{
  struct __cancel_jmp_buf_tag __cancel_jmp_buf[1];
  void *__pad[4];
} __pthread_unwind_buf_t __attribute__ ((__aligned__));
# 557 "/usr/include/pthread.h" 3 4
struct __pthread_cleanup_frame
{
  void (*__cancel_routine) (void *);
  void *__cancel_arg;
  int __do_it;
  int __cancel_type;
};
# 697 "/usr/include/pthread.h" 3 4
extern void __pthread_register_cancel (__pthread_unwind_buf_t *__buf)
     ;
# 709 "/usr/include/pthread.h" 3 4
extern void __pthread_unregister_cancel (__pthread_unwind_buf_t *__buf)
  ;
# 750 "/usr/include/pthread.h" 3 4
extern void __pthread_unwind_next (__pthread_unwind_buf_t *__buf)
     __attribute__ ((__noreturn__))

     __attribute__ ((__weak__))

     ;
# 766 "/usr/include/pthread.h" 3 4
extern int __sigsetjmp_cancel (struct __cancel_jmp_buf_tag __env[1], int __savemask) __asm__ ("" "__sigsetjmp") __attribute__ ((__nothrow__))


                     __attribute__ ((__returns_twice__));
# 781 "/usr/include/pthread.h" 3 4
extern int pthread_mutex_init (pthread_mutex_t *__mutex,
          const pthread_mutexattr_t *__mutexattr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_mutex_destroy (pthread_mutex_t *__mutex)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_mutex_trylock (pthread_mutex_t *__mutex)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_mutex_lock (pthread_mutex_t *__mutex)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));




extern int pthread_mutex_timedlock (pthread_mutex_t *__restrict __mutex,
        const struct timespec *__restrict
        __abstime) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
# 835 "/usr/include/pthread.h" 3 4
extern int pthread_mutex_unlock (pthread_mutex_t *__mutex)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_mutex_getprioceiling (const pthread_mutex_t *
      __restrict __mutex,
      int *__restrict __prioceiling)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_mutex_setprioceiling (pthread_mutex_t *__restrict __mutex,
      int __prioceiling,
      int *__restrict __old_ceiling)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3)));




extern int pthread_mutex_consistent (pthread_mutex_t *__mutex)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 874 "/usr/include/pthread.h" 3 4
extern int pthread_mutexattr_init (pthread_mutexattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_mutexattr_destroy (pthread_mutexattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_mutexattr_getpshared (const pthread_mutexattr_t *
      __restrict __attr,
      int *__restrict __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_mutexattr_setpshared (pthread_mutexattr_t *__attr,
      int __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_mutexattr_gettype (const pthread_mutexattr_t *__restrict
          __attr, int *__restrict __kind)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern int pthread_mutexattr_settype (pthread_mutexattr_t *__attr, int __kind)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_mutexattr_getprotocol (const pthread_mutexattr_t *
       __restrict __attr,
       int *__restrict __protocol)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern int pthread_mutexattr_setprotocol (pthread_mutexattr_t *__attr,
       int __protocol)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_mutexattr_getprioceiling (const pthread_mutexattr_t *
          __restrict __attr,
          int *__restrict __prioceiling)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_mutexattr_setprioceiling (pthread_mutexattr_t *__attr,
          int __prioceiling)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_mutexattr_getrobust (const pthread_mutexattr_t *__attr,
     int *__robustness)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
# 946 "/usr/include/pthread.h" 3 4
extern int pthread_mutexattr_setrobust (pthread_mutexattr_t *__attr,
     int __robustness)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 967 "/usr/include/pthread.h" 3 4
extern int pthread_rwlock_init (pthread_rwlock_t *__restrict __rwlock,
    const pthread_rwlockattr_t *__restrict
    __attr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlock_destroy (pthread_rwlock_t *__rwlock)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlock_rdlock (pthread_rwlock_t *__rwlock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlock_tryrdlock (pthread_rwlock_t *__rwlock)
  __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));




extern int pthread_rwlock_timedrdlock (pthread_rwlock_t *__restrict __rwlock,
           const struct timespec *__restrict
           __abstime) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
# 1023 "/usr/include/pthread.h" 3 4
extern int pthread_rwlock_wrlock (pthread_rwlock_t *__rwlock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlock_trywrlock (pthread_rwlock_t *__rwlock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));




extern int pthread_rwlock_timedwrlock (pthread_rwlock_t *__restrict __rwlock,
           const struct timespec *__restrict
           __abstime) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1, 2)));
# 1071 "/usr/include/pthread.h" 3 4
extern int pthread_rwlock_unlock (pthread_rwlock_t *__rwlock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));





extern int pthread_rwlockattr_init (pthread_rwlockattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlockattr_destroy (pthread_rwlockattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlockattr_getpshared (const pthread_rwlockattr_t *
       __restrict __attr,
       int *__restrict __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_rwlockattr_setpshared (pthread_rwlockattr_t *__attr,
       int __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_rwlockattr_getkind_np (const pthread_rwlockattr_t *
       __restrict __attr,
       int *__restrict __pref)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_rwlockattr_setkind_np (pthread_rwlockattr_t *__attr,
       int __pref) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







extern int pthread_cond_init (pthread_cond_t *__restrict __cond,
         const pthread_condattr_t *__restrict __cond_attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_cond_destroy (pthread_cond_t *__cond)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_cond_signal (pthread_cond_t *__cond)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_cond_broadcast (pthread_cond_t *__cond)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));






extern int pthread_cond_wait (pthread_cond_t *__restrict __cond,
         pthread_mutex_t *__restrict __mutex)
     __attribute__ ((__nonnull__ (1, 2)));
# 1145 "/usr/include/pthread.h" 3 4
extern int pthread_cond_timedwait (pthread_cond_t *__restrict __cond,
       pthread_mutex_t *__restrict __mutex,
       const struct timespec *__restrict __abstime)
     __attribute__ ((__nonnull__ (1, 2, 3)));
# 1194 "/usr/include/pthread.h" 3 4
extern int pthread_condattr_init (pthread_condattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_condattr_destroy (pthread_condattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_condattr_getpshared (const pthread_condattr_t *
     __restrict __attr,
     int *__restrict __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_condattr_setpshared (pthread_condattr_t *__attr,
     int __pshared) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_condattr_getclock (const pthread_condattr_t *
          __restrict __attr,
          __clockid_t *__restrict __clock_id)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_condattr_setclock (pthread_condattr_t *__attr,
          __clockid_t __clock_id)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 1230 "/usr/include/pthread.h" 3 4
extern int pthread_spin_init (pthread_spinlock_t *__lock, int __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_spin_destroy (pthread_spinlock_t *__lock)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_spin_lock (pthread_spinlock_t *__lock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_spin_trylock (pthread_spinlock_t *__lock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_spin_unlock (pthread_spinlock_t *__lock)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));






extern int pthread_barrier_init (pthread_barrier_t *__restrict __barrier,
     const pthread_barrierattr_t *__restrict
     __attr, unsigned int __count)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_barrier_destroy (pthread_barrier_t *__barrier)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_barrier_wait (pthread_barrier_t *__barrier)
     __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));



extern int pthread_barrierattr_init (pthread_barrierattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_barrierattr_destroy (pthread_barrierattr_t *__attr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_barrierattr_getpshared (const pthread_barrierattr_t *
        __restrict __attr,
        int *__restrict __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int pthread_barrierattr_setpshared (pthread_barrierattr_t *__attr,
        int __pshared)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 1297 "/usr/include/pthread.h" 3 4
extern int pthread_key_create (pthread_key_t *__key,
          void (*__destr_function) (void *))
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int pthread_key_delete (pthread_key_t __key) __attribute__ ((__nothrow__ , __leaf__));


extern void *pthread_getspecific (pthread_key_t __key) __attribute__ ((__nothrow__ , __leaf__));


extern int pthread_setspecific (pthread_key_t __key,
    const void *__pointer)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__access__ (__none__, 2)));




extern int pthread_getcpuclockid (pthread_t __thread_id,
      __clockid_t *__clock_id)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
# 1332 "/usr/include/pthread.h" 3 4
extern int pthread_atfork (void (*__prepare) (void),
      void (*__parent) (void),
      void (*__child) (void)) __attribute__ ((__nothrow__ , __leaf__));
# 1346 "/usr/include/pthread.h" 3 4

# 9 "queue.h" 2
# 55 "queue.h"

# 55 "queue.h"
struct _FIFO_1byte_{
    unsigned char *pop;
    unsigned char *head;
    unsigned char *tail;
    unsigned char *push;
 unsigned char (*popf)(unsigned char *n,struct _FIFO_1byte_ *s);
 unsigned char (*appendByte)(unsigned char n,struct _FIFO_1byte_ *s);
    void (*vaciarbuff)(unsigned char *p1,unsigned char *p2,unsigned short int size);
    void (*resetFIFO)(struct _FIFO_1byte_ *s,unsigned char *arr,unsigned char size);
    unsigned short int ncount;
    unsigned short int size;
    unsigned char nLibres;
    unsigned char nOcupados;
};



union _Byte5_{
 unsigned short int bytes1;
 struct{
  unsigned short FIFOonReset:1;
  unsigned short DDSon:1;
  unsigned short TxBuffOFF:1;
  unsigned short init_VFD:1;
  unsigned short init_Menu:1;
  unsigned short BOX_enable:1;

  unsigned short ADC_DATO:1;
  unsigned short deprecated1:1;
  unsigned short recurso_VFD_Ocupado:1;
        unsigned short Menu_Ready:1;
     unsigned short BorrarDDS:1;
        unsigned short MenuPendiente:1;

 }bits;
};

 struct _Sync{


 pthread_mutex_t mutex_free;
 pthread_cond_t cond_free;

};

struct _Sync2{
   pthread_cond_t *cond_free;
   pthread_mutex_t *m_Free;
   pthread_cond_t *cond_Tx;
   pthread_mutex_t *m_Tx;
   pthread_cond_t *cond_Mon;
   pthread_mutex_t *m_Mon;
   pthread_mutex_t VDF_busy;

};



struct VFD_DATA{
  unsigned char x;
  unsigned char y;
  unsigned char p;
};


struct Node{



  struct VFD_DATA dato;
  struct Node *next;
};




struct Queue{
  struct Node *head,*tail;
  int size;

    unsigned char nLibres;
 unsigned char nOcupados;
 unsigned char Tamano;

  struct _Sync2 s;
  unsigned char isPadreAlive;
  unsigned char *p;
  unsigned char sizeStream;
};





struct _FIFO_func_{

      unsigned char (*append)(struct Queue *q,struct VFD_DATA dato);
   unsigned char (*pop)(unsigned char *x,unsigned char *y, unsigned char *p);
   unsigned char (*resetFIFOS)(void);
};

struct FIFOc {
    uint8_t buffer[10];
    int head;
    int tail;
    int count;
};

struct _Contexto{
  unsigned char Actual;
  unsigned char Modificado;
  unsigned char destino;
  unsigned char control;
  unsigned char final;
  unsigned char permisos;
  unsigned char Anterior0;
  unsigned char Anterior1;
  unsigned char Anterior2;
  unsigned char Anterior3;
  unsigned char Anterior4;
  unsigned char solicitaCambioA;
        struct FIFOc fifo;
        int (*pop)( uint8_t *value);
  void (*push)(uint8_t value);
  int (*peek)( int position, uint8_t *value);
};



struct _KeyPAd_{
   unsigned char enable;
};


struct ZoomControl{
    signed short int Max;




    double zFactor;
    float indiceConversion;
    unsigned char Cx;
    unsigned char Cy;
    unsigned char Zoom;
    unsigned short int pixelSizeX;
    unsigned short int Maxx;
    unsigned short int pixelSizeY;
    unsigned short int Maxy;
    signed short int lapso;
    unsigned short int Ymax;
    unsigned short int Ymin;


    float (*factor)(unsigned char);
    struct Coordusi (*MaxZoom)(unsigned char);
};


struct _Comando_DDS{

 union Bytex{
    unsigned char Bnderas;
    struct{
     unsigned char DDS_Reload:1;
     unsigned char Apagando:1;
        unsigned char EventDDS:1;
     unsigned char DDS1_BORRAR:1;
     unsigned char DDS1_TIMER:1;
     unsigned char clean_Buffers:1;
     unsigned char Aspect_Zoom:1;
     unsigned char debug:1;
     unsigned char Gain_AB:1;
    }bit;
 }Bnderas;

 struct _Display_{
  unsigned char flag_TX_Pixel;
  unsigned short int delay;
 }display;

 struct _TOUCHSCREEN_{
  signed short int bufferX[50];
  signed short int bufferY[50];
  signed short int *headx;
  signed short int *tailx;
  signed short int *popx;
  signed short int *pushx;
  signed short int *heady;
  signed short int *taily;
  signed short int *popy;
  signed short int *pushy;
     unsigned char ncount;
 }touch;

 struct _SAVE_PIXELS_{
  signed short int xPixel[6];
  signed short int yPixel[6];
  signed short int *p[8];

  unsigned char ncount;



 }SaveTempPix;



    unsigned char (*remove)(signed short int *x,signed short int *y);
    unsigned char (*append)(signed short int x,signed short int y);

    struct _DispayPixel_{
     unsigned char *pop,*popx,*popy;
     unsigned char *push,*pushx,*pushy;
     unsigned char *tail,*tailx,*taily;
     unsigned char *head,*headx,*heady;
     unsigned char buffX[40];
     unsigned char buffY[40];
     unsigned char pen[40];

     unsigned char ncount;



    }pixel;

    struct _Repaint_ZOOM{


     unsigned char xy[129][24];
     unsigned char xy0[129][24];
     unsigned short int ii;
     unsigned char j,k,uy;
     unsigned char ix,iy,b;
     unsigned char x1[100],y1[100];
     unsigned short int debug5;
     unsigned short int debug6;
    }rePaint;

  struct ZoomControl zoom;

};

struct _Menu1_{
   struct _Contexto contexto;
   unsigned char cursorx;
   unsigned char cursory;
   struct _Comando_DDS dds;
   unsigned char CuadroMadreReady;


};

struct _Deteccion_{
       unsigned char EnCurso;


};


struct _PRODUCT1_{
   unsigned short int Cuenta_Rechazos;
   unsigned short int Cuenta_Productos;
   unsigned char CuentaProducto;
   unsigned short int Sensibilidad;
   unsigned char phase;
   float fase;
   unsigned char Phasefrac;
   unsigned char name[20];


};




struct _DISPLAY_VFD_{
 struct _FIFO_1byte_ x;
 struct _FIFO_1byte_ y;
 struct _FIFO_1byte_ p;
 struct _FIFO_func_ f1;
 union _Byte5_ config;
    struct _Sync2 mutex;
 struct Queue q;
 struct _Menu1_ menu;
 struct _KeyPAd_ keypad;
    struct _Deteccion_ deteccion;
 unsigned char Text[20];


  struct _box_control{
   unsigned char boxs[20];
   unsigned char box0;
   unsigned char box;
   unsigned short int timer;
      unsigned char enable;
    }box;

 struct _Vars_{
  unsigned char nbytes;
  unsigned char dat[14U];
  unsigned short int timer;
  unsigned short int timer_us;
  unsigned long int timer_ms;
  unsigned char index;
  unsigned char recurso;

    }v;

};






unsigned char FIFO_DDS_pop(unsigned char *dato);
void init_FIFO_DDS(void);
unsigned char isFIFO_DDS_empty(void);
unsigned char isFIFO_DDS_pixel_llena(void);
unsigned char isFIFO_DDS_pixel_empty(void);
unsigned char FIFO_DDS_pixel_pop(unsigned char *x,unsigned char *y,unsigned char *pen);
void display_DDS_transmitter_Controller(void);
void init_FIFO_DDS_Display_Pixel2(void);
void init_FIFO_DDS_Display_Pixel2_v2(void);
unsigned char isFIFO_DDS_Display_Pixel_llena2(void);
unsigned char isFIFO_DDS_Display_Pixel_empty2(void);
unsigned char FIFO_DDS_Display_Pixel_push(unsigned char datox,unsigned char datoy,unsigned char pen);
unsigned char FIFO_DDS_Display_Pixel_pop2(unsigned char *x,unsigned char *y,unsigned char *p);
unsigned char isFIFO_DDS_Display_Pixel_empty2_v2(void);
unsigned char *FIFO_DDS_next_X(unsigned char *p);
unsigned char isFIFO_DDS_Display_Pixel_empty2(void);
void init_FIFO_DDS_pixel(void);
void FIFO_DDS_pixels_push(unsigned char x,unsigned char y,unsigned char pen);
unsigned char FIFO_DDS_Display_Pixel_push(unsigned char datox,unsigned char datoy,unsigned char pen);
unsigned char isFIFO_DDS_Display_Pixel_llena2_v2(void);
unsigned char isFIFO_DDS_pixel_llena(void);
unsigned char isFIFO_DDS_Display_Pixel_empty_v2(void);
unsigned char isFIFO_DDS_pixel_empty(void);
unsigned char FIFO_DDS_Display_Pixel_pop2(unsigned char *x,unsigned char *y,unsigned char *p);
unsigned char FIFO_DDS_pixel_pop(unsigned char *x,unsigned char *y,unsigned char *pen);
void init_queues(void);
unsigned char FIFO_Display_DDS_Pixel_pop2(unsigned char *x,unsigned char *y,unsigned char *p);

unsigned char FIFO_Display_DDS_Pixel_pop2_v2(unsigned char *x,unsigned char *y,unsigned char *p);
unsigned char FIFO_Display_DDS_Pixel_push(unsigned char datox,unsigned char datoy,unsigned char pen);
unsigned char *FIFO_DDS_next_X(unsigned char *p);
unsigned char isFIFO_DDS_Display_Char_empty2(void);
void init_FIFO_DDS_Display_Char2(void);
unsigned char FIFO_Display_DDS_Char_pop2(unsigned char *x,unsigned char *y);
unsigned char FIFO_Display_DDS_Char_push(unsigned char datox,unsigned char datoy);
unsigned char *gotonext(unsigned char *last,unsigned char *first,unsigned char *tail);
unsigned char FIFO_displayBox_pop(void);

unsigned char FIFO_displayBox_push(unsigned char box);
unsigned char FIFO_displayBox_isEmpty(void);
void FIFO_Display_DDS_Char_clean(void);
void FIFO_Display_DDS_Pixel_clean(void);
unsigned char FIFObox_nextLast(void);
void malloc_display_Box(void);
unsigned char FIFOboxChars_nextLast(void);
unsigned char FIFO_displayBoxChars_pop(unsigned char *x,unsigned char *y);
unsigned char FIFO_displayBoxChar_push(unsigned char x,unsigned char y);
void malloc_display_Box_Chars(void);
signed short int popPushFIFO_OFFSET(signed short int *ry,signed short int xn,signed short int yn);
void init_FIFO_OFFSET(void);
void init_FIFOs_TX_IOUP(void);
unsigned char getComand_FIFO_B(unsigned char n);
unsigned char pushFIFO_TX(unsigned char cmd,unsigned char *dato);
signed short int **next2(signed short int *inicio,signed short int *final,signed short int **pos);

unsigned char isLoad_next(unsigned char **p);
void reset_pointer(void);
void pushFIFO_average_Offset(signed short int **pos,signed short int **pop,signed short int *tail,signed short int *ini,signed short int dato);
signed short int popFIFO_average_Offset(signed short int **pos,signed short int **pop,signed short int *tail,signed short int *ini);
unsigned char *next(unsigned char *inicio,unsigned char *final,unsigned char *pos,unsigned char *pop);
void init_FIFO_BARRA_NUMERO(void);
unsigned char FIFO_barraNum_push(unsigned char c);
void FIFO_barraNum_VFDposicion(unsigned char posx,unsigned char posy);
unsigned char FIFO_barraNum_pop(void);
unsigned char isFIFO_num_Not_Empty(void);
void FIFO_barraNum_VFDserial_SendChar(unsigned char c);
void init_FIFO_CMD_DDS(void);
void init_FIFO_TX_serial_General(void);
void vaciarBuffer(unsigned char *p,unsigned char *p2,unsigned short int size);
void push_FIFO_TRANSMISION_serial_IO(unsigned char byte);
unsigned char xpop_FIFO_CMD_DDS(signed short int *x,signed short int *y);
unsigned char push_FIFO_CMD_DDS(signed short int x,signed short int y);
unsigned char pop_FIFO_TRANSMISION_serial_IO(unsigned char *status);
void reset_FIFO_serial_TX(void);
unsigned char search_NO_Repetido(signed short int x,signed short int y);
void init_FIFO_SaveTemp_pixel_DDS(void);
unsigned char pop_FIFO_save_Temp_pixel_DDS(signed short int *x,signed short int *y);
unsigned char push_FIFO__save_Temp_pixel_DDS(signed short int x,signed short int y);
unsigned char is_FULL_FIFO_save_Temp_pixel_DDS(void);
unsigned char is_Empty_FIFO_save_Temp_pixel_DDS(void);
void clean_repaint_Pixels_DDS(void);
unsigned char IIC_FIFO_push_RX(unsigned char);
unsigned char IIC_FIFO_push_TX(unsigned char);
unsigned char IIC_FIFO_pop_RX(void);
unsigned char IIC_FIFO_pop_TX(void);
unsigned char get_Paquete(unsigned char *p,unsigned char (*pop)(void));
unsigned char is_device(unsigned char (*pop)(void),unsigned char *n);
unsigned char is_Lenght(unsigned char(*pop)(void),unsigned char *n);
unsigned char is_App(unsigned char(*pop)(void),unsigned char *n);
unsigned char is_CMD(unsigned char(*pop)(void),unsigned char *n,unsigned char app);
void get_parametros(unsigned char (*pop)(void),unsigned char *p);
void IIC_stop(void);
void init_FIFO_IIC(void);
void init_FIFO_RX_serial_Keypad(struct _FIFO_1byte_ *s);
unsigned char FIFO_general_1byte_push(unsigned char dato,struct _FIFO_1byte_ *s);

unsigned char FIFO_general_1byte_pop(unsigned char *dato,struct _FIFO_1byte_ *s);
void reset_FIFO_general_UChar(struct _FIFO_1byte_ *s,
            unsigned char *arr,unsigned char size);
void Testing_SO_Debug(void);
unsigned char vfd_FIFO_push(struct Queue *q,struct VFD_DATA dato);
unsigned char vfd_FIFO_pop(unsigned char *x,unsigned char *y,unsigned char *p);
unsigned char vfd_FIFOs_RESET(void);
void init_FIFO_General_1byte(struct _FIFO_1byte_ *s,
             unsigned char *h,unsigned char size);
unsigned char dds_pix_pop(signed short int *x,signed short int *y);
unsigned char dds_pix_append(signed short int x,signed short int y);
unsigned char dds_pix_reset(void);
void init_System_Monitor(void);
void reset_sys_mon(void);
void reset_sys_mon2(void);
unsigned char test_FIFOS_VFD(void);


void insertVFDProcess(unsigned char process);
unsigned char insertVFDProcess_(unsigned char process);
unsigned char Solicitar_Recurso(unsigned char Recurso,unsigned char pid);
unsigned char ya_esta_en_la_FIFO_VFD(unsigned char pid);
void get_parameters_to_process_PID(unsigned char *pid1,unsigned char *index,unsigned char pid);
unsigned char sacar_de_la_FIFO_vfd(unsigned char pid);
unsigned char insertarlo_en_Fifo_VFD(unsigned char pid);

unsigned char sacar_de_la_FIFO_IO(unsigned char pid);
unsigned char insertarlo_en_Fifo_IO(unsigned char pid);
unsigned char ya_esta_en_la_FIFO_IO(unsigned char pid);
void Devolver_Recurso_VFD(unsigned char recurso,unsigned char pid);
void init_queues(void);
void Terminar_subProcesos(void);
void* Init_VFD(void* arg);
unsigned char Transmissor_a_VFD(struct VFD_DATA v,unsigned char *mem);
void *Proceso_Limpiador(void *arg);


void init_Queue_with_Thread(struct Queue *q);


void init_menu(void);
void *Run_Menu(void *arg);





unsigned char procesar_Paquete(unsigned char cmd,unsigned char *c,unsigned char size);


void iniciar_Run_Menu(void);
void init_fifo_contexto(struct FIFOc *fifo);
int pop_contexto(struct FIFOc *fifo, uint8_t *value);
void push_contexto(struct FIFOc *fifo, uint8_t value);
int peek_contexto(struct FIFOc *fifo, int position, uint8_t *value);
void push_fifo_contexto(uint8_t dato);
int pop_fifo_contexto(uint8_t *value);
int peek_fifo_contexto(int position, uint8_t *value);
void configModificado(unsigned char contexto);
# 21 "VFDmenu.h" 2
# 749 "VFDmenu.h"
struct _Returns{
 union _Ret{
        unsigned char RetByte;
        struct{
        unsigned char fInit_VFD:1;
        unsigned char fInit_Menu:1;
        unsigned char x2:1;
        unsigned char x3:1;
        unsigned char x4:1;
        unsigned char x5:1;
        unsigned char x6:1;
        unsigned char x7:1;
        }bit;
  }u;
};


struct _Menu_{
 unsigned char debug43;
 struct _Contexto contexto;

 struct _Returns ret;
 struct _FIFO_1byte_ menus;
 void (*cambio_Contexto)(unsigned char contexto);
 union _Bytes_{
    unsigned char byteReg;
    struct{
  unsigned char MenuPendiente:1;
  unsigned char isBusy:1;
  unsigned char isMenu:1;
  unsigned char isCursor:1;
  unsigned char x3:1;
  unsigned char x4:1;
  unsigned char x5:1;
  unsigned char x6:1;
    }b;
  }b;
   struct _vars_{
   unsigned char aux[40];
   unsigned short int usi[4];
   float f[2];
   unsigned long int ulint[2];
  }v;
};




struct ArbolMenu{
    unsigned char menuNodo;
    unsigned char menuPadre;




    unsigned char permisos;


    void (*func)(void);
    unsigned char (*func1)(void);
    unsigned char (*func2)(unsigned char*);

    void (*funcKeyUP)(void);
    void (*funcKeyDN)(void);
    void (*funcKeyRT)(void);
    void (*funcKeyLF)(void);
    void (*funcKeyEN)(void);
};




typedef struct{
   unsigned char var1;
   unsigned char var2;
   float fvar1;
   unsigned char *editarSensFase;
   unsigned char *cursorAnterior;
   unsigned char *ResetDisplayNum;
   unsigned char *arg2;
}GlobalStruct;

extern GlobalStruct global;
extern GlobalStruct *AjParamProd,*ConfEntSyst;
extern GlobalStruct *MenuInfoUser;







unsigned char PortalinicioDisplay(void);
void menus(unsigned char key);

void cursorMenuControl(unsigned char keyx);
void DisplayIDcomunicaciones(void);
void displayIDcommNUM(void);
void DisplayControlFrecuencias(void);

unsigned char configModificacionController(unsigned char contextopadre,unsigned char contextomodificado1);
void displayMenuAjustedeProducto(void);
void DisplayMenuAjustedeSistema(void);
void DisplayMenuAdministrativo(void);
void DisplayConfigIOsistem(void);
void DisplayConfigIOsistem(void);
void DisplayEstaSeguro(void);
void displayIDcommNUM(void);

void DisplayMedidasVoltaje(void);
void DisplayAjusteProductoInfo(void);
void DisplayTiempoRechazo(void);
void DisplayAjusteSistemaEntradas(void);
void DisplayIDmaquina(void);
void DisplayCuentaProducto(void);
void DisplayMenuInformacionUsuario(void);
void DisplayAjusteSistemaEntradas(void);
void DisplayEstablecerIdioma(void);
void DisplayControlpassword(void);
void DisplayRelojSistema(void);
void DisplayIngenieriaGracida(void);
void displayAjusteGuardiaControl(void);
void DisplayInitMemoria_y_Restaurar(void);
void DisplayTipodeMaquina(void);
void DisplayMenuGanancia(void);
void DisplayMenuFiltro(void);
void filtroVarRotate(void);
void displayfiltroVar(void);
void DisplayIngenieriaGracida2(void);
void ReporteProductoVarRotate(void);
void DisplayAjusteParamProd(void);
void DisplayAjustesAvanzados(void);
void DisplayFrecuenciaSelect(void);
unsigned char displayFrecuenciaSelect_var(void);
void displayFrecuenciaSelect_active_var(void);
void DisplayPruebaMenu(void);
void DisplayI2CMenu(void);
void DisplayRelojSistemaVariables(void);
void DisplayI2CeepromData(void);
unsigned char getunidadHex(unsigned char n);
unsigned char getdecenaHex(unsigned char n);
void DisplayEEPROMdata(void);
void DisplayContrasenaVars(unsigned char psw);
void rotateAjusteGuardiavar(void);
void displayControldeUsuariovar(void);
void rotateControldeUsuariovar(void);
void DisplayI2CNVRAMdata(void);
void displaySegundos(void);
void DisplaySPIMenu(void);
void sendSPI_DSScomm(void);
void DisplayAjustesAvanzadosAPP(void);
void DisplayParametrosdeDeteccion(void);
void rotate_frecuencySelect_var(void);
void displayfrecuencySelect_var(void);

void displayADCsValues(void);
void displayADCvalor(signed short int *v,unsigned char posx,unsigned char posy);
void convert4(unsigned char *p,signed short int b,signed short int *n, signed short int k);
void convertBTC2chars(unsigned char *p,signed short int *dato);
char getDM(signed short int *n);
void Display_BIOS(void);

unsigned int displaytUINT_varxDigito(unsigned short int posx,unsigned short int posy,char operacion,unsigned short int digito,unsigned short int *pvar);
char displayPhase_varxDigito(unsigned short int posx, unsigned short int posy,char operacion,unsigned short int digitopos);
void displaySwitchGanancia_var(char pantalla,unsigned char operacion);
void displaySwitchCuadro_var(unsigned char operacion);

void convertSINT2UINT(signed short int sx,signed short int sy,unsigned short int *ux,unsigned short int *uy);
void displayDDS_Update(void);
void refreshDDS(unsigned char posy);
void DisplayPruebasSalidasMenu(void);
void prueba_SalidasON(unsigned char cursory,void (*func)(unsigned char));
void DisplayPruebasEntradasMenu(void);
void displayPruebasEntradas(void);
void MemoEEPROM_DDS(unsigned operacion,unsigned char contexto1,unsigned char mode);
void displaySeleccionarProducto(void);
unsigned short int lenght2(unsigned char *c);
void displayNuevoProducto(void);
void displayTextoProcessor(void);
unsigned char configTextoProcessorController(unsigned char contextOrigen,unsigned char contextDestino);
unsigned char TextMasterProcessorController(unsigned char contextOrigen,unsigned char contextDestino);
void displayEEPROMdata1(unsigned char *p);

void rotateVarParte11(void);
void displayvarParte11(void);
void DisplayParte11Menu(void);
void DisplayAjusteVibracionMenu(void);

unsigned char displayBoxDestructor(unsigned char mode);
void DisplayEstaSeguro2(void);
void displayBox(unsigned char *MutexCV);
unsigned char displayNumsMenuConfigVibracion(unsigned char *MutexCV1);

void pushFIFOcOP_displayUINT_var(unsigned short int posx,unsigned short int posy,unsigned short int *pn,unsigned char operacion);
void pushFIFOcOP_display5UChars(unsigned short int posx,unsigned short int posy,unsigned char *p);
void displayOperativoBarraDet_Numeros(void);
unsigned char getPosYNewProdDN(unsigned char sup,unsigned char iProd);
unsigned char getColTextProc(unsigned char dir);
void displayTextoProcessorMayusculas(void);
void displayTextoProcessorSymbol(void);
void displayTextoProcessorMinusculas(void);
char getAscii(unsigned char x,unsigned char y,unsigned char pantalla);
void DisplayNewTextProc(void);
void DisplayAjusteProductoMode(void);
void saveNewProduct(unsigned char iProd);

void displaySeleccionarProductoTitle(void);
void displayBorrarProducto(void);
void displayBorrarProductoTitle(void);
void displayCopyProducto(void);
void displayCopyProductoTitle(void);
void displayPasteProductoTitle(void);
void displayAjusteProductoSelectTitle(void);
void displayAjusteProductoSelect(void);
void displayNombreProductoEdit(void);
void control_Operativo_MenuEscape(void);
void displaySwitchAnaloga(void);
void displayRotateStatusSwapSwitchAnaloga(unsigned char pos);
void displayStateSwitchAnaloga(void);
void cursorMenuControlService(unsigned char key,struct ArbolMenu *Pantalla);
void displayTimer_IRQ(void);
void DebugSimulationKeyboard(void);

unsigned char isNotEmptyAllSelectMenu(void);
unsigned char BuscarSiguienteiProduct(unsigned char direccion);
void DisplayNuevoProducto(void (*func)(void));
void DisplayPasteProduct(void);
unsigned char display_centrarNombres(unsigned char nchars);
unsigned char length3(unsigned char *c);
unsigned char length3(unsigned char *c);
unsigned long int menu_delay(unsigned char op);
void displayNameProd(unsigned char *p,unsigned char posy);
void cleanBufferText(unsigned char *p);
void displayMarcarAltura(unsigned char posx,unsigned char posy);
void displayGanancia(unsigned char posx,unsigned char posy);
void DisplayAjusteTiempoRechazo(void );
void DisplayEntradaTestProducto(void);
void DisplayEntradaFotoCel(void);
void DisplayEntradaTaco(void);
void DisplayEntradaTestRechazo(void);
void displaySensorFotoCelda(unsigned char sensor,unsigned char bloqueado);
void DisplayEntradaAuxiliar1(void);
void DisplayEntradaAuxiliar2(void);
void displaySensorPruebaSistema(unsigned char sensor_seg,unsigned char sensor_ms,unsigned char posy);
void displayEntradaTest(unsigned char sensor,unsigned char sensorBloqueado,unsigned char seg,unsigned char mseg);
unsigned char *DebugVirtualEEPROMaux_userdef(unsigned char op,unsigned short add,unsigned char *w,unsigned short int nbytes);
void DisplayEntradaAuxiliar(unsigned char sensor,unsigned char rele,unsigned char seg,unsigned char mseg,unsigned char aux,unsigned char label);
void Cambiar_a_Portal_Inicio(void);
void DisplayMedidasVoltajes(void);
unsigned char Anti_Bounce_Keypad(unsigned char *c1);
unsigned char isEnable_Keypad(unsigned char cmd);
void DDS_Borrar_Refresh(void);
unsigned char isEnable_Keypad2(unsigned char cmd,unsigned long int maxtime);
void resetDDS_repetidos(unsigned short int n);
unsigned char procSensxDigitoLF(unsigned char posx,unsigned char posy,unsigned short int *Sens);
void procFasexDigitoEN(unsigned char *var,unsigned char posx,unsigned char posy);
void Cambio_de_Frecuencia_por_IIC_1(unsigned short int);
void prueba_SalidasOFF(unsigned char posy,void (*func)(unsigned char));
void keypad_Timer(void);

void display_Error(unsigned char x,unsigned char y,unsigned char *mens,unsigned char size);

unsigned char InitArbolMenu(unsigned char destino);


unsigned char displayMenuInsight(void);
unsigned char DDS_HANDLER(void);
void displaySwitchGanancia_var1(char pantalla,unsigned char operacion);
unsigned char InitArbolMenu2(unsigned char destino);
unsigned char xRun_Menu(unsigned char *p);
unsigned char cursorUpDown(unsigned char *inst);
unsigned char digitoUpDown(unsigned char *inst);
unsigned char digitoRtLeft(unsigned char *inst);
unsigned char enterCursorDDS(unsigned char *inst);
unsigned char enterCursorDDS_v2(unsigned char *inst);
unsigned char menus_service(unsigned char *mem);
unsigned char find_Next_Context(unsigned char *context);
void cambio_contexto(unsigned char contexto);
void display_Barra_Deteccion(unsigned char barra);
void display_CuentaRechazosProducto(unsigned char deteccion);
void display_Sens_Phase(unsigned short int sens,unsigned char phase,unsigned char phasefrac);
# 3 "VFDkey.c" 2
# 1 "VFDisplay.h" 1







extern struct _GLOBAL_CONTEXTO gxc,gxc2,gxc3,gxc4,gxc5;
# 22 "VFDisplay.h"
struct DPM{
 unsigned long int uli;
 unsigned short int usi;
 float f;
 unsigned char uc[15];
};
# 37 "VFDisplay.h"
void saveTextBuffer(unsigned char *p);
void Display_rotate_Ganancia_var(unsigned char posx,unsigned char posy);
void Display_rotate_MarcarAltura(unsigned char posx,unsigned char posy);

void convert2ascii(unsigned char *array,unsigned char size);
void display_pushFIFO_UShortInt(unsigned short *ShortNum,unsigned char index,unsigned char op,unsigned char Row,unsigned char contxt);
void display_UInt_CharsSelected(unsigned short int var,unsigned char *index,unsigned char posy,unsigned char posInit);
unsigned short int f2(unsigned char x);
void calculoOrdenCharsUInt_wSelectChar(unsigned char B1,unsigned char *b,unsigned char *a);
void displayOrdenCharsUInt_wSelectChar(unsigned char *bb,unsigned char *aa,unsigned char posInit,unsigned char posy);
unsigned char rotateSensor(unsigned char sensor);
void displaySensorActivation(unsigned char sensor, unsigned char pos);
unsigned char rotateSensorHighNibble(unsigned char sensor);
void displayUChar(unsigned char *p,unsigned short posx,unsigned short posy);
unsigned char getHighNibbleSensor(unsigned char sensor);
void displayAltoSiBajoSi_Sensor(unsigned char sensor,unsigned short posy);
unsigned char rotateCursorBloquedo(unsigned char sensorbloqueado,unsigned char *posicion);
void displayrotateCursorBloquedo(unsigned char sensorBloqueado,unsigned short posx,unsigned short posy,unsigned char *cursorSelect);
unsigned char displayBloqueoDigitoControl(unsigned char op,unsigned char *bloqueado,unsigned char *digito,unsigned char posx,unsigned char posy);
void displayControlCursorSubMenusKey(unsigned char direccion,unsigned char *posx, unsigned char *posy,unsigned char esqx,unsigned char *posiciones,unsigned char posx0);
void display_Prueba_de_Sistema(unsigned char segundo,unsigned char mseg,unsigned char *digito,unsigned char posx,unsigned char posy);
unsigned char rotate_Prueba_de_Sistema(unsigned char direccion,unsigned char *seg,unsigned char *mseg,unsigned char digito);
unsigned char *getLabelAux(unsigned char aux,unsigned char index);
void display_Permitir_No(unsigned char sensor,unsigned char posy);
void display_Alto_Bajo_Si(unsigned char sensor,unsigned char posy);
void display_LabelAux(unsigned char aux,unsigned char label,unsigned char posy);
void display_auxRele(unsigned char sensorRele,unsigned char posy);
void display_tiempo_activo_aux_label(unsigned char posy);
unsigned char rotateLabelAux(unsigned char label);
unsigned char rotate_auxRele(unsigned char sensorRele);
unsigned char displayPruebaSistema_float(unsigned char dir,unsigned char *seg,unsigned char *mseg,unsigned char *digito,unsigned char posy);
unsigned char DisplayInsertSpaceTextProc(unsigned char indice);
void DisplayCharTextProc(unsigned char pos,unsigned char dato);
void DisplayCursorTextProc(unsigned char pos_actual, unsigned char pos_anterior);
unsigned char DisplayRecorrerIndiceIzqTextProc(unsigned char ii,unsigned char IzqDer);
void display_Voltage_Mediciones(unsigned char *p,unsigned char voltaje,struct _GLOBAL_CONTEXTO *g,unsigned char signo);
void display_B_bold_DDS(unsigned char disp);
void displayPSU_IO_var(void);
void displayErrorAnalogoVar(void);
void displayReporteProductoVar(void);
void displayBorrarContadores_var(void);
void display_pushFIFOcOP_BorrarContadores_var(void);
void displayCountingBIOS_(unsigned char subsystem);
void displayBIOS_MEMO_test(unsigned char status,unsigned char memo);
void displayNuevoProductoTitle(void);
void displayNuevoProductoXY(unsigned short int y,void (*func)());
void displayNumbers(unsigned char n);
void displayEntradadeSistemas(unsigned char var);
void displayZoomDDS_var(unsigned char operacion);
unsigned short int displayZoomDDS_varxDigito(unsigned short int posx,unsigned char operacion);
void display_pushFIFOcOP_Phase_var(unsigned char posx,unsigned char posy);
void displayControlContrasenaVal(unsigned char varnum);
unsigned char displayTime(unsigned char t);
void displayGananciaValues(unsigned char tarjeta);
void displaySeleccioniProd_lugarOcupado(void(*func)(void));
unsigned char setLimitesMenuPROD(unsigned char mode);
void displayAnguloCompletado(void);
void displayAnguloVibracion(unsigned char Ang,unsigned char frac,unsigned char veces);
void displayZoom(unsigned char posx,unsigned char posy);
void display_Phase_DDS(unsigned char posx,unsigned char posy,unsigned char *p);
void display_Name_Product(unsigned posx,unsigned char posy);
void Display_Ajuste_Tiempo_Rechazo(void);
void save_Pixels(signed short int x1,signed short int y1,unsigned char ux,unsigned char uy);
unsigned char get_Pixels_Saved(signed short int *x,signed short int *y,unsigned char *ux4,unsigned char *uy4,unsigned char *swap);
unsigned char getRegistro_X_bit(unsigned char *Reg,unsigned char x);

void display_Sensibilidad_Geometrico(unsigned char v);
void display_Sensibility_Geometry_Line(unsigned char v);
void Display_Cuenta_Rechazos(unsigned short int rechazos);
unsigned short int f(unsigned char x);
void display_cursor_main(unsigned char *index);
void cambio_de_contexto(unsigned char destino);
void display_Sensibilidad_Limites(float angulo,unsigned short int sens);




unsigned char displayParametros(unsigned char *inst1,unsigned char *inst2);
unsigned char display_Float(unsigned char x,unsigned char y,unsigned char *inst,unsigned char *inst2);
unsigned char display_UShort_int(unsigned short int x,unsigned short int y,unsigned char *inst1,unsigned char *inst2);
unsigned char xDisplay_Parametros_PORTAL_INICIO_VFD(unsigned char *m);
unsigned char Display_Monitor_de_Rechazos_VFD(unsigned char *p);



unsigned char display_Linea_10_DDS(unsigned char DDSaux,unsigned char *inst);

void displayZoomDDS_var1(unsigned char operacion);
unsigned char Display_Monitor_de_Producto_VFD(unsigned char *p);
unsigned char Display_Monitor_de_Sensibilidad_VFD(unsigned char *p);

unsigned char xInit_Menu(unsigned char *p);

unsigned char xInit_VFD(unsigned char *p);
unsigned char Display_Monitor_de_Phase_VFD(unsigned char *p);
unsigned char xDisplay_Barra_Y_Parametros(unsigned char *m);

unsigned char display_B_bold_DDS_v2(unsigned char disp,unsigned char *inst);
unsigned char xDisplay_Cursores_DDS_VFD(unsigned char *inst);
unsigned char displayControlCursorSubMenusKey_v2(unsigned char direccion,unsigned char *posx, unsigned char *posy,unsigned char esqx,unsigned char *posiciones,unsigned char posx0,unsigned char *inst);
unsigned char xDisplay_Cursores_en_DDS_VFD(unsigned char *inst);
unsigned char display_Sens_Lim_v2(float angulo,unsigned short int sens,unsigned char *inst,unsigned short int *usi,float *f);
void getBoxPattern(unsigned char box,unsigned char *mode,unsigned char *x1,unsigned char *y1,unsigned char *x2,unsigned char *y2);
unsigned char find_contexto_Siguiente(void);
void BarraDet_displayUINT_var(unsigned char posx,unsigned char posy,unsigned short int *usint);
unsigned char digito2posicion(unsigned char digito);
void displayUINT_var(unsigned char posx,unsigned char posy,unsigned short int *pn,unsigned char operacion);
void display5UChars(unsigned char posx,unsigned char posy,unsigned char *p);
void displayPhase_var(unsigned char posx,unsigned char posy);
void DisplayCuentaProducto(void);
void procSensxDigitoEN(unsigned char *digito,unsigned char posx,unsigned char initx);
# 4 "VFDkey.c" 2

# 1 "VFD.h" 1
# 34 "VFD.h"
typedef uint8_t uchar;

typedef union{
 unsigned short int coord16;
 unsigned char byte[2];
}coordn16;


typedef struct {
    uchar datos[40];
    size_t longitud;
} bloque_t;
# 67 "VFD.h"
void VFDkeypad_ISR(unsigned char c);
void init_VFD_BIOS(void);
void VFDposicionDDS(unsigned short int x,unsigned short int y);
void VFDserial_SendCharDDS(unsigned char c);
void VFDdrawLine(unsigned char pen,unsigned short int x1,unsigned short y1,unsigned short int x2,unsigned short y2);




void BarraDet_VFDserial_SendChar(unsigned char c);



void VFDboxLine(unsigned char pen,unsigned char mode,unsigned short int x1,unsigned short y1,unsigned short int x2,unsigned short y2);
unsigned char VFDposicion(unsigned char x,unsigned char y);



void VFDcommand_Bold_DDS(unsigned char bold);
void BarraDet_VFDposicion(unsigned short int x,unsigned short int y);
void menuKey(unsigned char key,unsigned short int Et,unsigned char c);
void teclado_Control(unsigned char c,unsigned short int EnTime,unsigned short int Keytime);
unsigned char Basura(unsigned char c);
unsigned char VFDserial_SendChar(unsigned char c);





unsigned char VFDboxLine1(unsigned char pen,unsigned char mode,unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2);







void VFDclrscr(void);

void VFDdrawLine1(unsigned char pen,unsigned short int x1,unsigned short y1,unsigned short int x2,unsigned short y2);

unsigned char VFDcommand(unsigned char cmd);
unsigned char VFDcommand_init(unsigned char cmd);
unsigned char VFDdrawLine_v4(unsigned char pen,unsigned short int x1, unsigned short int y1,unsigned short int x2,unsigned short int y2,unsigned short int delay1,unsigned char *inst,unsigned short int *usi);
unsigned char VFDdrawLine_v5(unsigned char pen,unsigned short int x1, unsigned short int y1,unsigned short int x2,unsigned short int y2,unsigned short int delay1,unsigned char *inst,unsigned short int *usi,unsigned char PIDpadre);
void VFDcommand_Bold_DDS(unsigned char bold);
unsigned char VFDcommand_Bold_DDS_v2(unsigned char bold);
unsigned char FontSizeVFD(unsigned char m,unsigned char *mem);

void initParallelPort_Global(void);
void writePort(unsigned char value);
void test_display(void);


void VFD_sendChar(uchar c);
unsigned char inicializar_VFD(void);

unsigned char getCRC_v2(unsigned char *data, unsigned char len);

unsigned char VFDserial_SendBarraDet(unsigned char val);
unsigned char VFDserial_Sendusint(unsigned short int valor,unsigned char posx,unsigned char posy,unsigned char formato);
void VFDserial_SendPhase(unsigned char fase,unsigned char fasefrac,unsigned char posx,unsigned char posy,unsigned char formato);
unsigned char crc_Eval(unsigned char len, unsigned char cmd,unsigned char *param,unsigned char crc);
unsigned char VFDserial_SendBlock(const void *Ptr,unsigned char size1);
# 6 "VFDkey.c" 2
# 1 "system.h" 1
# 7 "VFDkey.c" 2
# 1 "maths.h" 1




union FloatChar {
 float f;
 unsigned char c[4];
};


struct Coorduc {
 unsigned char x;
 unsigned char y;
};

struct Coordssi{
 signed short int x;
 signed short int y;
};

struct Coordusi{
 unsigned short int x;
 unsigned short int y;
};


struct Coordsuc {
 struct Coorduc Pa;
 struct Coorduc Pb;
};


struct Coordf {
 float x;
 float y;
};

struct Coorducf{
  struct Coorduc uc;
  float f;
};

struct Coordsf {
 struct Coordf Pm;
 struct Coordf Pn;
};

struct Ec_Recta {
 float m;
 float b;
};

unsigned char recalcular_valor_Ser_Barr_det(unsigned char val);
struct Coordsf AgetEcuation(struct Ec_Recta* f, struct Coordf P1, float angulo);
struct Ec_Recta getEcuation(struct Coordf P1, struct Coordf P2);
struct Coordsf get_x2r(unsigned short int s, struct Ec_Recta f, struct Coordf P);
struct Coordsf get_Evaluar_(struct Coordsf P, struct Ec_Recta f);
double raizCuadrada(unsigned short int numero);
signed short int absSSInt(signed short int a);

double absd(double m);
float tan1(float deg);


void operacionPhase(unsigned char digito, unsigned char op);
void operacionUShortInt(unsigned short int* n, unsigned char digito, unsigned char op);
signed short int getMaximun(unsigned char zoom);
float redondearFloat(float f);
double convertir_ADC_word_A_miliVolt(unsigned short int ADCval, unsigned char channel);
double absd(double m);
float absf(float m);
signed short int absSSInt(signed short int a);

unsigned char FIFOcount(unsigned char var, unsigned char op);
void getBytes_from_SSInt(unsigned char* byteMSB, unsigned char* byteLSB, signed short int ssi);
unsigned char getSigno_Convert(signed short int* n);
unsigned char is_get_number_from_pixel(unsigned char* x, unsigned char* y);
void re_Calcular_Buffers_DDS_Modificar_Uno(unsigned char zoom1);
void re_Calcular_Buffers_DDS(unsigned char zoom_wished);
unsigned char get_Coord_Num(unsigned char xn, unsigned char bit);
unsigned char get_cuadrante(unsigned char xi, unsigned char yi);
void reconvertir_coord_reducir_uno(unsigned char xn, unsigned char yn, unsigned char cuadrante, unsigned char* xr, unsigned char* yr, unsigned char palanca);

float seno(float valor);
float tan1(float deg);
void generador_de_signal_Debug(signed short int* x, signed short int* y);
unsigned char convert_BCD_to_uchar(unsigned char BCD);
float convert_Phase_to_Float(unsigned char fase, unsigned char frac);
double raizCuadrada(unsigned short int numero);
float raizCuadf(float r);
float tanr(float x);
struct Ec_Recta getEcuation(struct Coordf P1, struct Coordf P2);
struct Coordsf AgetEcuation(struct Ec_Recta* f, struct Coordf P1, float angulo);
void cifras(float r, int* aprox, int* miniaprox);
struct Coordsf get_Puntos_Perpendiculares(float m, struct Coordf P, unsigned short int s);

struct Coordsf get_x2r(unsigned short int s, struct Ec_Recta f, struct Coordf P);
struct Coordsf get_Evaluar_(struct Coordsf P, struct Ec_Recta f);
float get_Float_Fase(unsigned char* p);
struct Coordf get_Evaluar(struct Coordf P, struct Ec_Recta f);
float Raiz2(float num);
float atan1(double a);
float rad_a_deg(double rad);
float deg_a_rad(double deg);
struct Coordsf AgetEcuation2(struct Ec_Recta* f, struct Coordf P1, float angulo);
unsigned char getFloat_uchar(float n);
unsigned char getFloat_Frac(float n);
struct Coordsf AgetEcuation3(struct Ec_Recta *g,struct Ec_Recta f, struct Coordf P, float angulo);
double tan4(double angulo);
double sin(double g);
double cos(double g);
float pow1(double num1, unsigned char pot);
double factorial(unsigned char a);


struct Coordsf get_Evaluar_3(struct Coordsf P,struct Ec_Recta f);
struct Coordsf get_Evaluar_2(struct Coordsf P,struct Ec_Recta f,float angulo);
float frecta(struct Ec_Recta* f,char c, float x);
struct Ec_Recta resolvEcuation(struct Coordf P1, struct Coordf P2);

struct Ec_Recta getEcuacion_Recta(struct Coordf P1,float angulo);
struct Coordsf get_Puntos_Perpendiculares(float m, struct Coordf P, unsigned short int s) ;
struct Coordsf get_Puntos(struct Ec_Recta f,float angulo,unsigned char linea,unsigned short int s);
float calculo_pendiente_inversa(float ang);
struct Ec_Recta getEcuacion_Recta_Punto_Pendiente(struct Coordf P,float m);
float pow1f(float num1, unsigned char pot);
struct Coordsf busqueda_Puntos_Altura(struct Ec_Recta f,unsigned short int s);
float get_angulo_Perpendicular(float m,float angulo);
struct Coordf get_Puntos_de_Interseccion(struct Ec_Recta f,struct Ec_Recta g);
float Obtener_Mitad_Recta(float M,float m);
struct Coordf Buscar_Punto_en_Recta_auna_Distancia(unsigned char dir,struct Ec_Recta f,struct Coordf P,unsigned short int s);
float Buscar_Maximo_para_Busqueda_Binaria(unsigned char Dir,float i,struct Ec_Recta f, struct Coordf P,unsigned short int s);
float dist2Pnts(struct Ec_Recta f,struct Coordf P1,struct Coordf P2);
double Raizd(double num);
double pow1d(double num1, unsigned char pot);
float distancia_Entre_Puntos(struct Ec_Recta f,struct Coordf P1,float x2);
float Busqueda_Binaria_de_un_Punto(float xM,struct Ec_Recta f,struct Coordf P1,unsigned short int s,float e, float xmin);
struct Coorducf get_MaxDDSzoom(unsigned char zoom);
unsigned char inZoom(struct Coordsf P1,unsigned char zoom1);
unsigned char isCoords_inZoom(struct Coordsf P1,unsigned char zoom1);


struct Coordusi Maximo_Zoom(unsigned char z);

struct Coordf Centrar_Puntos_en_DDS(struct Coordf P);
unsigned char isDisplayable_in_ACtual_Zoom(struct Coordf P,unsigned char zoom1);
unsigned char find_Cuadrante(struct Coordf P);
struct Coordf Centrar_Puntos_en_DDS(struct Coordf P);
unsigned long int absul(long int m);

struct Coordsuc traducirCoordenadas_to_VFD(struct Coordsf f );
unsigned char getCheckSUM(unsigned char cmd, unsigned char *data, unsigned char len);
# 8 "VFDkey.c" 2
# 1 "strings.h" 1



unsigned short int length(unsigned char *c,unsigned char size);
void insertChar(unsigned char *s,unsigned char size,unsigned char index,unsigned char c);
unsigned char isNumLetter(char a);
void getCharsFromUINT_var(unsigned char *p,unsigned short int var);
void convertir_usint_to_BCD(unsigned char *p,unsigned short int var);
void suma_BCD_digito(unsigned char op,unsigned char n,unsigned char *p);
unsigned char func_Alge(unsigned char x);
unsigned char Formato_USInt(unsigned char *orig,unsigned char *dest,unsigned char size,unsigned char *n);
void vaciar_A2B(unsigned char *a,unsigned char *b,unsigned char i,unsigned char f);
void get_5_Chars_to_ASCII(unsigned char *array);
void format_Right(unsigned char *array);
void format_Left(unsigned char *array);
void format_Center(unsigned char *array);
void getASCIIFromUChar1(unsigned char n,unsigned char *cc);
 unsigned char procesar_Frac_Fase(unsigned char frac);
 void Formato_uChar(char *array, unsigned char format);
 unsigned char strcpy2(char *dest,char *orig,unsigned char size );
 unsigned char getCharsFromFloat(unsigned char *frac,float f);
void getUChar2Chars(unsigned char *p,unsigned char n ,char modoAscii);
float get_Float_from_Phase(unsigned char f,unsigned char fr);


unsigned char compareString(unsigned char *a,unsigned char *b,unsigned char size);
void getASCIIFromUChar1(unsigned char n,unsigned char *cc);

void getCharsFromUINT_var(unsigned char *p,unsigned short int var);

unsigned char voltagePositivo_a_Chars(double voltaje,unsigned char *N);
unsigned char convertir_Voltaje_A_Chars(double voltaje,unsigned char *N,unsigned char tarjeta);
unsigned char convertir_SignedShortInt_A_Char(signed short int ss,unsigned char *p);
unsigned short int convertCharstoUINT(unsigned char *p);
unsigned char findLastChar(unsigned char *s,unsigned char size);
void TextInsertSpace(unsigned char indice);
unsigned char TextBackSpace(unsigned char indice);
unsigned char isNum(char a);
void convertNum2Chars(unsigned char *p,unsigned char size);
unsigned char Procesamiento_con_Signo(unsigned char *p);
unsigned char Procesamiento_con_Signo2(unsigned char *p,unsigned char signo);
unsigned char isNumAscii(char a);
void convertir_usint_to_BCD(unsigned char *p,unsigned short int var);
void suma_BCD(unsigned char dm1,unsigned char m1,unsigned char c1,unsigned char d1,unsigned char u1,unsigned char *p);
void suma_BCD_digito(unsigned char op,unsigned char n,unsigned char *p);
void getASCII_from_UChar(unsigned char n,unsigned char *p);
unsigned char procesar_ASCII(unsigned char *p,unsigned char op,unsigned char digito);
unsigned char convert_ASCII_to_char(unsigned char *p);
void operacion_ASCII_Phase2(unsigned char digito,unsigned char op,unsigned char *p);
void getASCII_from_Fase(unsigned char *p,unsigned char fase,unsigned char frac);
void setASCII_to_Fase(unsigned char *p,unsigned char *fase,unsigned char *frac);
unsigned short int sizeof1(unsigned char *p,unsigned short int size);
void vaciar_A2B(unsigned char *a,unsigned char *b,unsigned char i,unsigned char f);
void cleanArray(unsigned char *arr,unsigned short int size,unsigned char k);
void swapArrays(unsigned char *a,unsigned char *b,unsigned char size);
void cleanArrayName(unsigned char *a,unsigned char size,unsigned char k,unsigned char m);
void insertChar(unsigned char *s,unsigned char size,unsigned char index,unsigned char c);
void getCharFromFloat(unsigned char *p,float f);
void getASCIIFromFloat(unsigned char *p,float f);
float get_Float_From_ASCII(unsigned char *p);
unsigned char strcpy1(unsigned char *dest,unsigned char *orig,unsigned char size );

void getASCIIfromUCharArray(unsigned char *orig,unsigned char *dest,unsigned char size);

unsigned char get_Char2ASCII(unsigned char *orig,unsigned char *dest,unsigned char size);
unsigned char Formato_Phase(unsigned char *orig);
void suma_BCD2(unsigned char a5,unsigned char a4,unsigned char a3,unsigned char a2,unsigned char a1,unsigned char dm1,unsigned char m1,unsigned char c1,unsigned char d1,unsigned char u1,unsigned char *p);
void convertir_ULInt_to_ASCII(unsigned char *p,unsigned long int var);
void suma_BCD_digito2(unsigned char op,unsigned char n,unsigned char *p,unsigned char flo);
unsigned char Formato_ULInt(unsigned char i,unsigned char *p);

unsigned char getCharsFromUINT_var1(unsigned char *p,unsigned short int var,unsigned char *v);
void clearFormato(unsigned char *a);
# 9 "VFDkey.c" 2
# 1 "/usr/include/stdlib.h" 1 3 4
# 26 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/libc-header-start.h" 1 3 4
# 27 "/usr/include/stdlib.h" 2 3 4





# 1 "/usr/lib/gcc/aarch64-linux-gnu/12/include/stddef.h" 1 3 4
# 329 "/usr/lib/gcc/aarch64-linux-gnu/12/include/stddef.h" 3 4

# 329 "/usr/lib/gcc/aarch64-linux-gnu/12/include/stddef.h" 3 4
typedef unsigned int wchar_t;
# 33 "/usr/include/stdlib.h" 2 3 4







# 1 "/usr/include/aarch64-linux-gnu/bits/waitflags.h" 1 3 4
# 41 "/usr/include/stdlib.h" 2 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/waitstatus.h" 1 3 4
# 42 "/usr/include/stdlib.h" 2 3 4
# 56 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/floatn.h" 1 3 4
# 23 "/usr/include/aarch64-linux-gnu/bits/floatn.h" 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/long-double.h" 1 3 4
# 24 "/usr/include/aarch64-linux-gnu/bits/floatn.h" 2 3 4
# 95 "/usr/include/aarch64-linux-gnu/bits/floatn.h" 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/floatn-common.h" 1 3 4
# 24 "/usr/include/aarch64-linux-gnu/bits/floatn-common.h" 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/long-double.h" 1 3 4
# 25 "/usr/include/aarch64-linux-gnu/bits/floatn-common.h" 2 3 4
# 96 "/usr/include/aarch64-linux-gnu/bits/floatn.h" 2 3 4
# 57 "/usr/include/stdlib.h" 2 3 4


typedef struct
  {
    int quot;
    int rem;
  } div_t;



typedef struct
  {
    long int quot;
    long int rem;
  } ldiv_t;





__extension__ typedef struct
  {
    long long int quot;
    long long int rem;
  } lldiv_t;
# 98 "/usr/include/stdlib.h" 3 4
extern size_t __ctype_get_mb_cur_max (void) __attribute__ ((__nothrow__ , __leaf__)) ;



extern double atof (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;

extern int atoi (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;

extern long int atol (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;



__extension__ extern long long int atoll (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;



extern double strtod (const char *__restrict __nptr,
        char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern float strtof (const char *__restrict __nptr,
       char **__restrict __endptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern long double strtold (const char *__restrict __nptr,
       char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 177 "/usr/include/stdlib.h" 3 4
extern long int strtol (const char *__restrict __nptr,
   char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern unsigned long int strtoul (const char *__restrict __nptr,
      char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



__extension__
extern long long int strtoq (const char *__restrict __nptr,
        char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

__extension__
extern unsigned long long int strtouq (const char *__restrict __nptr,
           char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));




__extension__
extern long long int strtoll (const char *__restrict __nptr,
         char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

__extension__
extern unsigned long long int strtoull (const char *__restrict __nptr,
     char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 386 "/usr/include/stdlib.h" 3 4
extern char *l64a (long int __n) __attribute__ ((__nothrow__ , __leaf__)) ;


extern long int a64l (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;




# 1 "/usr/include/aarch64-linux-gnu/sys/types.h" 1 3 4
# 27 "/usr/include/aarch64-linux-gnu/sys/types.h" 3 4






typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;


typedef __loff_t loff_t;




typedef __ino_t ino_t;
# 59 "/usr/include/aarch64-linux-gnu/sys/types.h" 3 4
typedef __dev_t dev_t;




typedef __gid_t gid_t;




typedef __mode_t mode_t;




typedef __nlink_t nlink_t;




typedef __uid_t uid_t;





typedef __off_t off_t;
# 103 "/usr/include/aarch64-linux-gnu/sys/types.h" 3 4
typedef __id_t id_t;




typedef __ssize_t ssize_t;





typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;





typedef __key_t key_t;
# 144 "/usr/include/aarch64-linux-gnu/sys/types.h" 3 4
# 1 "/usr/lib/gcc/aarch64-linux-gnu/12/include/stddef.h" 1 3 4
# 145 "/usr/include/aarch64-linux-gnu/sys/types.h" 2 3 4



typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;







typedef __uint8_t u_int8_t;
typedef __uint16_t u_int16_t;
typedef __uint32_t u_int32_t;
typedef __uint64_t u_int64_t;


typedef int register_t __attribute__ ((__mode__ (__word__)));
# 176 "/usr/include/aarch64-linux-gnu/sys/types.h" 3 4
# 1 "/usr/include/endian.h" 1 3 4
# 35 "/usr/include/endian.h" 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/byteswap.h" 1 3 4
# 33 "/usr/include/aarch64-linux-gnu/bits/byteswap.h" 3 4
static __inline __uint16_t
__bswap_16 (__uint16_t __bsx)
{

  return __builtin_bswap16 (__bsx);



}






static __inline __uint32_t
__bswap_32 (__uint32_t __bsx)
{

  return __builtin_bswap32 (__bsx);



}
# 69 "/usr/include/aarch64-linux-gnu/bits/byteswap.h" 3 4
__extension__ static __inline __uint64_t
__bswap_64 (__uint64_t __bsx)
{

  return __builtin_bswap64 (__bsx);



}
# 36 "/usr/include/endian.h" 2 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/uintn-identity.h" 1 3 4
# 32 "/usr/include/aarch64-linux-gnu/bits/uintn-identity.h" 3 4
static __inline __uint16_t
__uint16_identity (__uint16_t __x)
{
  return __x;
}

static __inline __uint32_t
__uint32_identity (__uint32_t __x)
{
  return __x;
}

static __inline __uint64_t
__uint64_identity (__uint64_t __x)
{
  return __x;
}
# 37 "/usr/include/endian.h" 2 3 4
# 177 "/usr/include/aarch64-linux-gnu/sys/types.h" 2 3 4


# 1 "/usr/include/aarch64-linux-gnu/sys/select.h" 1 3 4
# 30 "/usr/include/aarch64-linux-gnu/sys/select.h" 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/select.h" 1 3 4
# 31 "/usr/include/aarch64-linux-gnu/sys/select.h" 2 3 4


# 1 "/usr/include/aarch64-linux-gnu/bits/types/sigset_t.h" 1 3 4






typedef __sigset_t sigset_t;
# 34 "/usr/include/aarch64-linux-gnu/sys/select.h" 2 3 4



# 1 "/usr/include/aarch64-linux-gnu/bits/types/struct_timeval.h" 1 3 4







struct timeval
{




  __time_t tv_sec;
  __suseconds_t tv_usec;

};
# 38 "/usr/include/aarch64-linux-gnu/sys/select.h" 2 3 4





typedef __suseconds_t suseconds_t;





typedef long int __fd_mask;
# 59 "/usr/include/aarch64-linux-gnu/sys/select.h" 3 4
typedef struct
  {






    __fd_mask __fds_bits[1024 / (8 * (int) sizeof (__fd_mask))];


  } fd_set;






typedef __fd_mask fd_mask;
# 91 "/usr/include/aarch64-linux-gnu/sys/select.h" 3 4

# 102 "/usr/include/aarch64-linux-gnu/sys/select.h" 3 4
extern int select (int __nfds, fd_set *__restrict __readfds,
     fd_set *__restrict __writefds,
     fd_set *__restrict __exceptfds,
     struct timeval *__restrict __timeout);
# 127 "/usr/include/aarch64-linux-gnu/sys/select.h" 3 4
extern int pselect (int __nfds, fd_set *__restrict __readfds,
      fd_set *__restrict __writefds,
      fd_set *__restrict __exceptfds,
      const struct timespec *__restrict __timeout,
      const __sigset_t *__restrict __sigmask);
# 153 "/usr/include/aarch64-linux-gnu/sys/select.h" 3 4

# 180 "/usr/include/aarch64-linux-gnu/sys/types.h" 2 3 4





typedef __blksize_t blksize_t;






typedef __blkcnt_t blkcnt_t;



typedef __fsblkcnt_t fsblkcnt_t;



typedef __fsfilcnt_t fsfilcnt_t;
# 230 "/usr/include/aarch64-linux-gnu/sys/types.h" 3 4

# 396 "/usr/include/stdlib.h" 2 3 4






extern long int random (void) __attribute__ ((__nothrow__ , __leaf__));


extern void srandom (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));





extern char *initstate (unsigned int __seed, char *__statebuf,
   size_t __statelen) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern char *setstate (char *__statebuf) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







struct random_data
  {
    int32_t *fptr;
    int32_t *rptr;
    int32_t *state;
    int rand_type;
    int rand_deg;
    int rand_sep;
    int32_t *end_ptr;
  };

extern int random_r (struct random_data *__restrict __buf,
       int32_t *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern int srandom_r (unsigned int __seed, struct random_data *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern int initstate_r (unsigned int __seed, char *__restrict __statebuf,
   size_t __statelen,
   struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4)));

extern int setstate_r (char *__restrict __statebuf,
         struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));





extern int rand (void) __attribute__ ((__nothrow__ , __leaf__));

extern void srand (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));



extern int rand_r (unsigned int *__seed) __attribute__ ((__nothrow__ , __leaf__));







extern double drand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern double erand48 (unsigned short int __xsubi[3]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern long int lrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int nrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern long int mrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int jrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern void srand48 (long int __seedval) __attribute__ ((__nothrow__ , __leaf__));
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void lcong48 (unsigned short int __param[7]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





struct drand48_data
  {
    unsigned short int __x[3];
    unsigned short int __old_x[3];
    unsigned short int __c;
    unsigned short int __init;
    __extension__ unsigned long long int __a;

  };


extern int drand48_r (struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int erand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int lrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int nrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int mrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int jrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern int seed48_r (unsigned short int __seed16v[3],
       struct drand48_data *__buffer) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern int lcong48_r (unsigned short int __param[7],
        struct drand48_data *__buffer)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern __uint32_t arc4random (void)
     __attribute__ ((__nothrow__ , __leaf__)) ;


extern void arc4random_buf (void *__buf, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern __uint32_t arc4random_uniform (__uint32_t __upper_bound)
     __attribute__ ((__nothrow__ , __leaf__)) ;




extern void *malloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__))
     __attribute__ ((__alloc_size__ (1))) ;

extern void *calloc (size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__alloc_size__ (1, 2))) ;






extern void *realloc (void *__ptr, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__)) __attribute__ ((__alloc_size__ (2)));


extern void free (void *__ptr) __attribute__ ((__nothrow__ , __leaf__));







extern void *reallocarray (void *__ptr, size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__))
     __attribute__ ((__alloc_size__ (2, 3)))
    __attribute__ ((__malloc__ (__builtin_free, 1)));


extern void *reallocarray (void *__ptr, size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__ (reallocarray, 1)));



# 1 "/usr/include/alloca.h" 1 3 4
# 24 "/usr/include/alloca.h" 3 4
# 1 "/usr/lib/gcc/aarch64-linux-gnu/12/include/stddef.h" 1 3 4
# 25 "/usr/include/alloca.h" 2 3 4







extern void *alloca (size_t __size) __attribute__ ((__nothrow__ , __leaf__));






# 588 "/usr/include/stdlib.h" 2 3 4





extern void *valloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__))
     __attribute__ ((__alloc_size__ (1))) ;




extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;




extern void *aligned_alloc (size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__alloc_align__ (1)))
     __attribute__ ((__alloc_size__ (2))) ;



extern void abort (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));



extern int atexit (void (*__func) (void)) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







extern int at_quick_exit (void (*__func) (void)) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));






extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern void exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));





extern void quick_exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));





extern void _Exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));




extern char *getenv (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
# 667 "/usr/include/stdlib.h" 3 4
extern int putenv (char *__string) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern int setenv (const char *__name, const char *__value, int __replace)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));


extern int unsetenv (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));






extern int clearenv (void) __attribute__ ((__nothrow__ , __leaf__));
# 695 "/usr/include/stdlib.h" 3 4
extern char *mktemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 708 "/usr/include/stdlib.h" 3 4
extern int mkstemp (char *__template) __attribute__ ((__nonnull__ (1))) ;
# 730 "/usr/include/stdlib.h" 3 4
extern int mkstemps (char *__template, int __suffixlen) __attribute__ ((__nonnull__ (1))) ;
# 751 "/usr/include/stdlib.h" 3 4
extern char *mkdtemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
# 804 "/usr/include/stdlib.h" 3 4
extern int system (const char *__command) ;
# 821 "/usr/include/stdlib.h" 3 4
extern char *realpath (const char *__restrict __name,
         char *__restrict __resolved) __attribute__ ((__nothrow__ , __leaf__)) ;






typedef int (*__compar_fn_t) (const void *, const void *);
# 841 "/usr/include/stdlib.h" 3 4
extern void *bsearch (const void *__key, const void *__base,
        size_t __nmemb, size_t __size, __compar_fn_t __compar)
     __attribute__ ((__nonnull__ (1, 2, 5))) ;







extern void qsort (void *__base, size_t __nmemb, size_t __size,
     __compar_fn_t __compar) __attribute__ ((__nonnull__ (1, 4)));
# 861 "/usr/include/stdlib.h" 3 4
extern int abs (int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern long int labs (long int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;


__extension__ extern long long int llabs (long long int __x)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;






extern div_t div (int __numer, int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern ldiv_t ldiv (long int __numer, long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;


__extension__ extern lldiv_t lldiv (long long int __numer,
        long long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
# 893 "/usr/include/stdlib.h" 3 4
extern char *ecvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;




extern char *fcvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;




extern char *gcvt (double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3))) ;




extern char *qecvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qfcvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qgcvt (long double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3))) ;




extern int ecvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int fcvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));

extern int qecvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int qfcvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));





extern int mblen (const char *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));


extern int mbtowc (wchar_t *__restrict __pwc,
     const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));


extern int wctomb (char *__s, wchar_t __wchar) __attribute__ ((__nothrow__ , __leaf__));



extern size_t mbstowcs (wchar_t *__restrict __pwcs,
   const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__ , __leaf__))
    __attribute__ ((__access__ (__read_only__, 2)));

extern size_t wcstombs (char *__restrict __s,
   const wchar_t *__restrict __pwcs, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__access__ (__write_only__, 1, 3)))
  __attribute__ ((__access__ (__read_only__, 2)));






extern int rpmatch (const char *__response) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
# 980 "/usr/include/stdlib.h" 3 4
extern int getsubopt (char **__restrict __optionp,
        char *const *__restrict __tokens,
        char **__restrict __valuep)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2, 3))) ;
# 1026 "/usr/include/stdlib.h" 3 4
extern int getloadavg (double __loadavg[], int __nelem)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 1036 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/aarch64-linux-gnu/bits/stdlib-float.h" 1 3 4
# 1037 "/usr/include/stdlib.h" 2 3 4
# 1048 "/usr/include/stdlib.h" 3 4

# 10 "VFDkey.c" 2
# 1 "errorController.h" 1
# 21 "errorController.h"

# 21 "errorController.h"
void errorCritico(char *c);
void NoErrorOK(void);
void mensOK(const char *s,unsigned char color);
void errorCritico2(char *c,unsigned char n);
void mens_Warnning_Debug(char *c);
# 11 "VFDkey.c" 2

extern struct _DISPLAY_VFD_ vfd;
extern struct _PRODUCT1_ producto2;


void PortaliniciokeyUP(void){return;}
void PortaliniciokeyRT(void){return; }
void PortaliniciokeyLF(void){return;}
void PortaliniciokeyDN(void){return;}
void PortaliniciokeyEN(void){

                          cambio_de_contexto(0xA2U);
                             return;}


void MenuInsightkeyUP(void){
unsigned char *cursorx,*cursory;
       cursorx=&vfd.menu.cursorx;
       cursory=&vfd.menu.cursory;
                            if(*cursory>((unsigned char)4)){
                              VFDposicion(*cursorx,*cursory);
                              VFDserial_SendChar(' ');
                              --(*cursory);
                              VFDposicion(*cursorx,--(*cursory));
                              VFDserial_SendChar('>');}
                         else
                          if(*cursory==((unsigned char)4)){
                           VFDposicion(*cursorx,*cursory);
                        VFDserial_SendChar(' ');
                        *cursorx=235;*cursory=((unsigned char)0);
                        VFDposicion(*cursorx,*cursory);
                        VFDserial_SendChar('>');
                        VFDserial_SendChar('X'); }
                          return;}
void MenuInsightkeyRT(void){return;}
void MenuInsightkeyLF(void){return;}
void MenuInsightkeyDN(void){
unsigned char *cursorx,*cursory;
       cursorx=&vfd.menu.cursorx;
       cursory=&vfd.menu.cursory;
                         if(*cursory==((unsigned char)0)){
                         VFDposicion(*cursorx,*cursory);
       VFDserial_SendChar(' ');
       VFDserial_SendChar('x');
       *cursorx=0;*cursory=((unsigned char)4);
       VFDposicion(*cursorx,*cursory);
       VFDserial_SendChar('>');
       return;}
             else{
             if(*cursory<((unsigned char)12)){
       VFDposicion(*cursorx,*cursory);
       VFDserial_SendChar(' ');
       ++(*cursory);
       VFDposicion(*cursorx,++(*cursory));
       VFDserial_SendChar('>');
       return;}}
                      return;}
void MenuInsightkeyEN(void){
unsigned char *cursorx,*cursory;
cursorx=&vfd.menu.cursorx;
cursory=&vfd.menu.cursory;
  switch(*cursory){
  case ((unsigned char)4): cambio_de_contexto(0xA4U);break;
  case ((unsigned char)6): cambio_de_contexto(0xDB);break;
  case ((unsigned char)8): cambio_de_contexto(0xA3U);break;
  case ((unsigned char)10):cambio_de_contexto(0xDE);break;
  case ((unsigned char)12):cambio_de_contexto(0xD4);break;
  case ((unsigned char)0): cambio_de_contexto(0xA1U);break;
  default:break;}
}





void AjusteProductokeyUP(void){
unsigned char *cursorx,*cursory;
       cursorx=&vfd.menu.cursorx;
       cursory=&vfd.menu.cursory;
                       if(*cursory>((unsigned char)4)){
                  VFDposicion(*cursorx,*cursory);
                  VFDserial_SendChar(' ');
                  --(*cursory);
                  VFDposicion(*cursorx,--(*cursory));
                  VFDserial_SendChar('>');
                  return;}
                 else if(*cursory==((unsigned char)4)){VFDposicion(*cursorx,*cursory);
                                         VFDserial_SendChar(' ');
                                         *cursorx=235;*cursory=((unsigned char)0);
                                         VFDposicion(*cursorx,*cursory);
                                         VFDserial_SendChar('>');
                                         VFDserial_SendChar('X'); }
                       return;}
void AjusteProductokeyRT(void){return; }
void AjusteProductokeyLF(void){return;}
void AjusteProductokeyDN(void){
unsigned char *cursorx,*cursory;
       cursorx=&vfd.menu.cursorx;
       cursory=&vfd.menu.cursory;
 if(*cursory==((unsigned char)0)){
   VFDposicion(*cursorx,*cursory);
   VFDserial_SendChar(' ');
   VFDserial_SendChar('x');
   *cursorx=0;*cursory=((unsigned char)4);
   VFDposicion(*cursorx,*cursory);
   VFDserial_SendChar('>');return;}
 else{if(*cursory<((unsigned char)14)){
     switch(vfd.menu.contexto.control){
      case 0x4F:if(*cursory>=((unsigned char)6)){
                        *cursory=((unsigned char)6);
                           return;}

      case 0x41:
      case 0xC8:
      case 0x53:
           VFDposicion(*cursorx,*cursory);
           VFDserial_SendChar(' ');
          ++(*cursory);
           VFDposicion(*cursorx,++(*cursory));
           VFDserial_SendChar('>');
           return;break;
      default:return;break; }}}
return;}
void AjusteProductokeyEN(void){
unsigned char *cursorx,*cursory,anterior;
 cursorx=&vfd.menu.cursorx;
 cursory=&vfd.menu.cursory;
 switch(*cursory){
  case ((unsigned char)4): break;
  case ((unsigned char)6): cambio_de_contexto(0xBBU); break;
     case ((unsigned char)8): cambio_de_contexto(0xBCU);
                    break;
  case ((unsigned char)10):cambio_de_contexto(0xC5); break;
  case ((unsigned char)12):cambio_de_contexto(0xC3); break;
  case ((unsigned char)14):cambio_de_contexto(0xC4);break;
  case ((unsigned char)0):cambio_de_contexto(0xA1U);break;
  default:break;}
}




void AjusteParamProdkeyUP(void){
unsigned char *cursorx,*cursory;
cursorx=&vfd.menu.cursorx;
cursory=&vfd.menu.cursory;

 if(*(AjParamProd->editarSensFase)>0){
     operacionVariable(168 -8,*cursory,*(AjParamProd->editarSensFase),0x80);
   configModificado(0xDB);

   return;}
 if(*cursory==((unsigned char)6)){
  VFDposicion(*cursorx,*cursory);
  VFDserial_SendChar(' ');
  *cursory=((unsigned char)0);
  VFDposicion(235,*cursory);
  VFDserial_SendChar('>');
  VFDserial_SendChar('X');
  VFDserial_SendChar(0x01);
  return;}
 if(*cursory==((unsigned char)0)){return;}
 if(*cursory<=((unsigned char)14)){
   VFDposicion(*cursorx,*cursory);
   VFDserial_SendChar(' ');
   --(*cursory);
   VFDposicion(*cursorx,--(*cursory));
   VFDserial_SendChar('>');
   VFDserial_SendChar(0x01);
   return;}
}
void AjusteParamProdkeyDN(void){
unsigned char *cursorx,*cursory;
 cursorx=&vfd.menu.cursorx;
 cursory=&vfd.menu.cursory;
 if(*(AjParamProd->editarSensFase)>0){
  operacionVariable(168 -8,*cursory,*(AjParamProd->editarSensFase),0x40);
  return;}
 if(*cursory==((unsigned char)0)){
    VFDposicion(235,((unsigned char)0));
    VFDserial_SendChar(' ');
    VFDserial_SendChar('x');
    *cursory=((unsigned char)6);
    VFDposicion(*cursorx,*cursory);
    VFDserial_SendChar('>');
    VFDserial_SendChar(0x01);
    return;}
 if(*cursory<((unsigned char)14)){
    VFDposicion(*cursorx,*cursory);
    VFDserial_SendChar(' ');
    (*cursory)++;
    VFDposicion(*cursorx,++(*cursory));
    VFDserial_SendChar('>');
    VFDserial_SendChar(0x01);
    return;}
}
void AjusteParamProdkeyRT(void){
unsigned char *cursorx,*cursory;
unsigned char phasefrac,phase;
 cursorx=&vfd.menu.cursorx;
 cursory=&vfd.menu.cursory;
 if(*cursory==((unsigned char)6)){
  procSensxDigitoRT(168,((unsigned char)6),&producto2.Sensibilidad);
     configModificado(0xDB);
  return;}
 if(*cursory==((unsigned char)8)){
  phase=getCharsFromFloat(&phasefrac,producto2.fase);
  if(++phasefrac>9){
   phasefrac=0;
   if(++phase>179){
    phase=0;
    phasefrac=0;}}
  display_pushFIFOcOP_Phase_var(168,((unsigned char)8));
  configModificado(0xDB);
  return;}
}
void AjusteParamProdkeyLF(void){
unsigned char *cursorx,*cursory;
unsigned char phasefrac,phase;

 cursorx=&vfd.menu.cursorx;
 cursory=&vfd.menu.cursory;
 if(*cursory==((unsigned char)6)){
    procSensxDigitoLF(168,((unsigned char)6),&producto2.Sensibilidad);
    configModificado(0xDB);}
    if(*cursory==((unsigned char)8)){
     phase=getCharsFromFloat(&phasefrac,producto2.fase);
     if(phasefrac!=0)
      phasefrac--;
     else{phasefrac=9;
    if(phase==0)
     phase=179;
      else phase--;}
     display_pushFIFOcOP_Phase_var(168,((unsigned char)8));
     configModificado(0xDB);
        producto2.fase=get_Float_from_Phase(phase,phasefrac);
     return;}
}
void AjusteParamProdkeyEN(void){

unsigned char *cursory;
        cursory=&vfd.menu.cursory;
     switch(*cursory){
      case ((unsigned char)2): break;
      case ((unsigned char)4): break;
      case ((unsigned char)6): procSensxDigitoEN(AjParamProd->editarSensFase,168 -8,0);
                  break;
      case ((unsigned char)8): procFasexDigitoEN(AjParamProd->editarSensFase,168,((unsigned char)10));
      break;
   case ((unsigned char)10):
            configModificado(0xDB);
      cambio_de_contexto(configModificacionController(0xDB,0xDB));
      *(AjParamProd->arg2)=26;
      break;
   case ((unsigned char)12):cambio_de_contexto(0xDE); break;
   case ((unsigned char)14):




      cambio_de_contexto(0xB5U);
      break;
   case ((unsigned char)0):cambio_de_contexto(0xA1U);
            break;
   default:
             errorCritico("Error en AjParamProd-Enter");
       exit(1);
            }




void AjustedeSistemakeyUP(void){
unsigned char *cursorx,*cursory;
  cursorx=&vfd.menu.cursorx;
  cursory=&vfd.menu.cursory;
     if(*cursory>((unsigned char)4)){
           VFDposicion(*cursorx,*cursory);
           VFDserial_SendChar(' ');
           --(*cursory);
           VFDposicion(*cursorx,--(*cursory));
           VFDserial_SendChar('>');
           return;}
        else
         if(*cursory==((unsigned char)4)){
          VFDposicion(*cursorx,*cursory);
                VFDserial_SendChar(' ');
                *cursorx=235;*cursory=((unsigned char)0);
                VFDposicion(*cursorx,*cursory);
                VFDserial_SendChar('>');
                VFDserial_SendChar('X'); }
return;}
void AjustedeSistemakeyRT(void){
return;}
void AjustedeSistemakeyLF(void){
 return;}
void AjustedeSistemakeyDN(void){
unsigned char *cursorx,*cursory;
  cursorx=&vfd.menu.cursorx;
  cursory=&vfd.menu.cursory;
    if(*cursory==((unsigned char)0)){
     VFDposicion(*cursorx,*cursory);
     VFDserial_SendChar(' ');
     VFDserial_SendChar('x');
     *cursorx=0;*cursory=((unsigned char)4);
     VFDposicion(*cursorx,*cursory);
     VFDserial_SendChar('>');return;}
      else{
       if(*cursory<((unsigned char)14)){
        switch(vfd.menu.contexto.control){
         case 1:
         case 2:return;break;
         case 3:
         case 4:if(*cursory==((unsigned char)12)){
                  return;break;}
         case 5:VFDposicion(*cursorx,*cursory);
            VFDserial_SendChar(' ');
                ++(*cursory);
                VFDposicion(*cursorx,++(*cursory));
                VFDserial_SendChar('>');
         default: return;break;
        }}}
return;}
void AjustedeSistemakeyEN(void){
unsigned char *cursorx,*cursory;
 cursorx=&vfd.menu.cursorx;
 cursory=&vfd.menu.cursory;
 if(*cursory==((unsigned char)2)){ return;}
 if(*cursory==((unsigned char)4)){ cambio_de_contexto( 0xD6); return;}
 if(*cursory==((unsigned char)6)){ cambio_de_contexto(0xC0); return;}
 if(*cursory==((unsigned char)8)){ cambio_de_contexto(0xD1);



          return;}
 if(*cursory==((unsigned char)10)){cambio_de_contexto(0xD3);return;}
 if(*cursory==((unsigned char)12)){cambio_de_contexto(0xD2); return;}
 if(*cursory==((unsigned char)14)){cambio_de_contexto(0xA9U); return;}
 if(*cursory==((unsigned char)0)){ cambio_de_contexto(0xA1U); return;}
return; }




void MenuInformacionUsuariokeyUP(void){
unsigned char *cursorx,*cursory;
  cursorx=&vfd.menu.cursorx;
  cursory=&vfd.menu.cursory;
 if(*cursory==((unsigned char)2)){
     VFDposicion(0,((unsigned char)2));
     VFDserial_SendChar(' ');*cursory=((unsigned char)0);
     VFDposicion(227,*cursory);
     VFDserial_SendChar('>');VFDserial_SendChar('X');
     return;}
   if(*cursory==((unsigned char)0)) return;
   if(*cursory<(((unsigned char)14)+1)){
     VFDposicion(0,*cursory);
     VFDserial_SendChar(' ');--(*cursory);
     VFDposicion(0,--(*cursory));
     VFDserial_SendChar('>'); return;}
}
void MenuInformacionUsuariokeyRT(void){return;}
void MenuInformacionUsuariokeyLF(void){return;}
void MenuInformacionUsuariokeyDN(void){
unsigned char *cursorx,*cursory;
  cursorx=&vfd.menu.cursorx;
  cursory=&vfd.menu.cursory;
 if(*cursory==((unsigned char)0)){
     VFDposicion(227,((unsigned char)0));
     VFDserial_SendChar(' ');VFDserial_SendChar('x');
     *cursorx=0;*cursory=((unsigned char)2);
     VFDposicion(*cursorx,*cursory);
     VFDserial_SendChar('>'); return;}
   if(*cursory==((unsigned char)14)){
     return;}
   if(*cursory<((unsigned char)14)){
   VFDposicion(0,*cursory);
   VFDserial_SendChar(' ');
   *cursorx=0;++(*cursory);
   VFDposicion(*cursorx,++(*cursory));
   VFDserial_SendChar('>'); return;}
}
void MenuInformacionUsuariokeyEN(void){
unsigned char *cursorx,*cursory;
unsigned char k;
  cursorx=&vfd.menu.cursorx;
  cursory=&vfd.menu.cursory;
 if(*cursory==((unsigned char)2)) { return;}
 if(*cursory==((unsigned char)4)) {*(MenuInfoUser->ResetDisplayNum)=0;
                  cambio_de_contexto(0xABU); return;}
 if(*cursory==((unsigned char)6)) { return;}
 if(*cursory==((unsigned char)8)) {cambio_de_contexto(0xADU); return;}
 if(*cursory==((unsigned char)10)){cambio_de_contexto(0xAEU); return;}
 if(*cursory==((unsigned char)12)){cambio_de_contexto(0xAFU); return;}
 if(*cursory==((unsigned char)14)){DisplayCuentaProducto(); return;}
 if(*cursory==((unsigned char)0)) {vfd.menu.contexto.peek(1,&k);
                      switch(k){
       case 0xA3U:cambio_de_contexto(k);break;
       case 0xA2U:cambio_de_contexto(k);break;
       default:cambio_de_contexto(0xA1U);break;}}
}
# 453 "VFDkey.c"
void operacionVariable(unsigned char posx,unsigned short int y,unsigned char igxm0,unsigned char op){
unsigned char a[5],*p,i,b[6];

unsigned char phase,phasefrac,*cursorx,*cursory;
  p=&a[0];
  cursorx=&vfd.menu.cursorx;
  cursory=&vfd.menu.cursory;
  switch(y){
   case ((unsigned char)6):
   case ((unsigned char)2):
     operacionUShortInt(&producto2.Sensibilidad,igxm0,op);
     *cursorx=posx;
     VFDposicion(*cursorx,*cursory);
     getCharsFromUINT_var(p,producto2.Sensibilidad);
     switch(igxm0){
      case 5:b[0]='>';
       b[1]=a[0]+0x30;
       b[2]=a[1]+0x30;
       b[3]=a[2]+0x30;
       b[4]=a[3]+0x30;
       b[5]=a[4]+0x30;
             break;
      case 4:b[0]=a[0]+0x30;
             b[1]='>';
             b[2]=a[1]+0x30;
             b[3]=a[2]+0x30;
             b[4]=a[3]+0x30;
             b[5]=a[4]+0x30;
             break;
      case 3:b[0]=a[0]+0x30;
       b[1]=a[1]+0x30;
       b[2]='>';
       b[3]=a[2]+0x30;
       b[4]=a[3]+0x30;
       b[5]=a[4]+0x30;
       break;
      case 2:b[0]=a[0]+0x30;
       b[1]=a[1]+0x30;
       b[2]=a[2]+0x30;
       b[3]='>';
       b[4]=a[3]+0x30;
       b[5]=a[4]+0x30;
       break;
      case 1:b[0]=a[0]+0x30;
       b[1]=a[1]+0x30;
       b[2]=a[2]+0x30;
       b[3]=a[3]+0x30;
       b[4]='>';
       b[5]=a[4]+0x30;
       break;
      default:break;}
   for(i=0;i<6;i++)
    VFDserial_SendChar(b[i]);
      break;
  case ((unsigned char)8):
     case ((unsigned char)4):
        phase=getCharsFromFloat(&phasefrac,producto2.phase);
     if(phasefrac>9)
      phasefrac=0;
     getASCII_from_Fase(&a[0],phase,phasefrac);

     operacion_ASCII_Phase2(igxm0,op,&a[0]);
     producto2.phase=get_Float_From_ASCII(&a[0]);


     setASCII_to_Fase(&a[0],&phase,&phasefrac);
     producto2.phase=get_Float_from_Phase(phase,phasefrac);

     break;
   default:break;}
}

unsigned char procSensxDigitoRT(unsigned char posx,unsigned char posy,unsigned short int *Sens){
 if((*Sens)>=32000)
   return 0;
 else ++(*Sens);
 BarraDet_displayUINT_var(posx,posy,Sens);
return 1;
}
