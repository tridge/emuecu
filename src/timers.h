#ifndef _TIMERS_H_
#define _TIMERS_H_

extern volatile uint32_t timer_0_1ms_;
extern volatile uint32_t timer_1_ovf_;
extern volatile uint32_t timer_2_ovf_;

inline uint16_t tcnt1_()
{
  uint16_t cnt = TCNT1L;
  cnt |= (TCNT1H << 8);
  return cnt;
}

inline uint32_t tcnt1_long_()
{
  return tcnt1_() + (timer_1_ovf_ << 16);
}

inline uint32_t tcnt1_us_()
{
  return (tcnt1_() >> 1) + (timer_1_ovf_ << 15);
}

inline uint16_t tcnt0_()
{
  uint16_t cnt = TCNT0;
  return cnt;
}

void setup_timers();

uint32_t ticks_us();
uint16_t ticks_ms();
void sleep(int ms);

#endif
