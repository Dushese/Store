#include <iostream>
#include<locale.h>
#include"PriceBase.h"



int main()
{
	//add some words
	setlocale(LC_ALL, "Russian");
	Order order;
	if (order.empty())
	{
		std::cout << "Ïóñòîé!\n";
	}
	auto& base = PriceBase::Instance();
	WeightProduct apple(base.get_product_weight_price("Apple"));
	AmountProduct pencil(base.get_product_amount_price("Pensile"));
	WeightPosition pos_apple(apple, 0.5);
	AmountPosition pos_pen(pencil, 2);
	order.add_position(&pos_apple);
	order.add_position(&pos_pen);
	order.get_info();
	WeightPosition other_pos_apple(apple, 1.5);
	order.add_position(&other_pos_apple);	
	order.get_info();
	Client Ivan;
	Ivan.pay_and_recieve_order(order);
	Ivan.earn_money(500);
	Ivan.pay_and_recieve_order(order);
	std::cout << "Çàêàç ïóñò? " << order.empty() << '\n';
	return 0;
	// add something...
}
