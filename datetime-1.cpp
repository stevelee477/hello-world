#include <iostream>
class DateTime {
private:
  int seconds;     //从1970年1月1日0时开始计算的秒数 
  int year, month, day;
  int hour, minute, second;
public:
  DateTime();
  DateTime(int y, int m, int d, int hour, int minute, int second); 
  DateTime(const DateTime &dt);
  ~DateTime();
  void showTime();
  void showMoon();  //作业：将当前公历转换为农历显示出来 
  void showSecond();
  void calcSecond();

  static bool isRunYear(int year);
  static int second_per_day;
  static int day_per_month[13];
};

int DateTime::second_per_day = 24 * 60 * 60;
int DateTime::day_per_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main() {
  DateTime dt, dt1(2020, 3, 27, 10, 40, 55);
  DateTime dt2(dt), &dt3 = dt;
  DateTime *dt4 = &dt;
  dt.showTime();
  dt1.showTime();
  dt2.showTime();
  dt3.showTime();
  dt4->showTime();
  dt1.showSecond();
  return 0;
}
DateTime::DateTime()
{
  year = 1970; month = 1; day = 1;
  hour = minute = second = 0;
  calcSecond();
}
DateTime::DateTime(int y, int m, int d, int _hour, int _minute, int _second)
{
  year = y; month = m; day = d;
  hour = _hour; minute = _minute; second = _second;
  calcSecond();
}
DateTime::DateTime(const DateTime &dt)
{
  year = dt.year; month = dt.month; day = dt.day;
  hour = dt.hour; minute = dt.minute; second = dt.second;
  second = dt.second;
}
DateTime::~DateTime() 
{
  std::cout << " Go die, Ha~Ha~" << std::endl;
}
void DateTime::showTime()
{
  printf("当前时间：%d/%d/%d %d:%d:%d\n", year, month, day, hour, minute, second);
}
 
void DateTime::showMoon() {
  int nTheDate = 0;
  int nisEnd = 0, flag = 0, n = 0, k = 0, nBit = 0, i = 0;
  char m_Lunar[100] = {0}, m_LunarDay[50] = {0}, m_zodiak[50] = {0};
  /*天干名称*/
  const char *m_TianGan[] = {"甲", "乙", "丙", "丁", "戊",
                             "己", "庚", "辛", "壬", "癸"};
  /*地支名称*/
  const char *m_DiZhi[] = {"子", "丑", "寅", "卯", "辰", "巳",
                           "午", "未", "申", "酉", "戌", "亥"};
  /*属相名称*/
  const char *m_ShuXiang[] = {"鼠", "牛", "虎", "兔", "龙", "蛇",
                              "马", "羊", "猴", "鸡", "狗", "猪"};
  /*农历日期名*/
  const char *m_DayName[] = {
      "*",    "初一", "初二", "初三", "初四", "初五", "初六", "初七",
      "初八", "初九", "初十", "十一", "十二", "十三", "十四", "十五",
      "十六", "十七", "十八", "十九", "二十", "廿一", "廿二", "廿三",
      "廿四", "廿五", "廿六", "廿七", "廿八", "廿九", "三十"};
  /*农历月份名*/
  const char *m_MonthName[] = {"*",  "正", "二", "三", "四",   "五", "六",
                               "七", "八", "九", "十", "十一", "腊"};
  /*公历每月前面的天数*/
  const int m_DayAdd[12] = {0,   31,  59,  90,  120, 151,
                            181, 212, 243, 273, 304, 334};
  /*农历数据*/
  const int m_LunarData[100] = {
      2635,   333387, 1701,   1748,   267701, 694,    2391,   133423, 1175,
      396438, 3402,   3749,   331177, 1453,   694,    201326, 2350,   465197,
      3221,   3402,   400202, 2901,   1386,   267611, 605,    2349,   137515,
      2709,   464533, 1738,   2901,   330421, 1242,   2651,   199255, 1323,
      529706, 3733,   1706,   398762, 2741,   1206,   267438, 2647,   1318,
      204070, 3477,   461653, 1386,   2413,   330077, 1197,   2637,   268877,
      3365,   531109, 2900,   2922,   398042, 2395,   1179,   267415, 2635,
      661067, 1701,   1748,   398772, 2742,   2391,   330031, 1175,   1611,
      200010, 3749,   527717, 1452,   2742,   332397, 2350,   3222,   268949,
      3402,   3493,   133973, 1386,   464219, 605,    2349,   334123, 2709,
      2890,   267946, 2773,   592565, 1210,   2651,   395863, 1323,   2707,
      265877};

  nTheDate = (year - 1921) * 365 + (year - 1921) / 4 + m_DayAdd[month - 1] +
             day - 31 - 7;
  if ((!(year % 4)) && (month > 2))
    nTheDate = nTheDate + 1;
  nisEnd = 0;
  flag = 0;
  while (nisEnd != 1) {
    if (m_LunarData[flag] < 4095)
      k = 11;
    else
      k = 12;
    n = k;
    while (n >= 0) {
      // m_LunarData(flag)的第n个二进制位的值
      nBit = m_LunarData[flag];
      for (i = 1; i < n + 1; i++)
        nBit = nBit / 2;
      nBit = nBit % 2;
      if (nTheDate <= (29 + nBit)) {
        nisEnd = 1;
        break;
      }
      nTheDate = nTheDate - 29 - nBit;
      n = n - 1;
    }
    if (nisEnd)
      break;
    flag = flag + 1;
  }
  year = 1921 + flag;
  month = k - n + 1;
  day = nTheDate;
  if (k == 12) {
    if (month == m_LunarData[flag] / 65536 + 1)
      month = 1 - month;
    else if (month > m_LunarData[flag] / 65536 + 1)
      month = month - 1;
  }
  /*--生成农历天干、地支、属相*/
  sprintf(m_zodiak, "%s", m_ShuXiang[((year - 4) % 60) % 12]);
  sprintf(m_Lunar, "%s%s年 【%s年】", m_TianGan[((year - 4) % 60) % 10],
          m_DiZhi[((year - 4) % 60) % 12], m_zodiak);
  /*--生成农历月、日*/
  if (month < 1)
    sprintf(m_LunarDay, "闰%s", m_MonthName[-1 * month]);
  else
    strcpy(m_LunarDay, m_MonthName[month]);
  strcat(m_LunarDay, "月");
  strcat(m_LunarDay, m_DayName[day]);

  printf("%s\n", m_LunarDay);
  printf("%s\n", m_Lunar);
  
}

void DateTime::calcSecond() {
  int days = 0;
  for (int y = 1970; y < year; y++) {
    if (DateTime::isRunYear(y)) {
      days += 366;
    } else {
      days += 365;
    }
  }
  for (int m = 1; m < month; m++) {
    if (m == 2 && DateTime::isRunYear(year))
      days += DateTime::day_per_month[m] + 1;
    else
      days += DateTime::day_per_month[m];
  }
  days += day - 1;

  second += days * DateTime::second_per_day;
  seconds += (hour - 1) * 60 * 60;
  seconds += (minute - 1) * 60;
  seconds += seconds;
}

bool DateTime::isRunYear(int year) {
  if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
    return true;
  }
  return false;
}

void DateTime::showSecond() {
  std::cout << "Second since 1970/01/01 00:00:00 is " << second << std::endl;  
}