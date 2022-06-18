#pragma once
#include"Order.h"

class Balance {
public:
	void add_money(const double& money) {
		m_money += money;
	}
	bool waste_money(const double& money)
	{
		if (m_money >= money) {
			m_money -= money;
			return true;
		}
		else return false;
	}
private:
	double m_money;
};
class Client {
public:
	Client() = default;
	void earn_money(double money) { m_balance.add_money(money); }
	bool pay_and_recieve_order(Order& order)
	{
		if (m_balance.waste_money(order.get_cost()))
		{
			order.clear();
			std::cout << "\nЗаказ успешно оплачен! \n";
			return true;
		}
		else {
			std::cout << "\nНедостаточно средств! Пополните баланс.\n";
			return false;
		}
	}

private:
	Balance m_balance;
};
