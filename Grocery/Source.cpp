#include <iostream>
#include<locale.h>
#include"PriceBase.h"


int main()
{
	setlocale(LC_ALL, "Russian");
	auto& base = PriceBase::Instance();
	Order order;
	if (order.empty())
	{
		std::cout << "Пустой!\n";
	}
	WeightPosition pos_apple(std::make_unique<WeightProduct>(base.get_product_weight_price("Apple")), 0.5);
	AmountPosition pos_pen(std::make_unique<AmountProduct>(base.get_product_amount_price("Pensile")), 2);
	order.add_position(std::make_unique<WeightPosition>(std::move(pos_apple)));
	order.add_position(std::make_unique<AmountPosition>(std::move(pos_pen)));
	order.get_info();

	WeightPosition other_pos_apple(std::make_unique<WeightProduct>(base.get_product_weight_price("Apple")), 1.5);
	order.add_position(std::make_unique<WeightPosition>(std::move(other_pos_apple)));
	order.get_info();

	Client Ivan;
	Ivan.pay_and_recieve_order(order);
	Ivan.earn_money(500);
	Ivan.pay_and_recieve_order(order);
	std::cout << "Заказ пуст? " << order.empty() << '\n'; 

	WeightPosition pos_nuts(std::make_unique<WeightProduct>(base.get_product_weight_price("Nuts")), 5);
	order.add_position(std::make_unique<WeightPosition>(std::move(pos_nuts)));
	order.get_info();
	Ivan.pay_and_recieve_order(order);

	return 0;
}