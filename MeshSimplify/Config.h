#pragma once
class Config
{
public:
	Config(void);
	~Config(void);
	static const int MAX_POINT_NUM = 1000000; // ��ඥ����
	static const int MAX_POINT_EDGE_NUM = 20000000;
	static const double EPS;  //����С������0
	static const double INF;  //�����
};