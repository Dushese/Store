#include <iostream>
#include<locale.h>
#include"PriceBase.h"



int main()
{
	setlocale(LC_ALL, "Russian");
	/*WeightProduct carr(ProductInfo("морковь"), 13.5);
	AmountProduct candy(ProductInfo("конфетка"), 5);
	std::cout << carr.get_info() << candy.get_info() << '\n';
	AmountPosition candies(candy, 10);
	WeightPosition carrots(carr, 4.5);
	std::cout << candies.get_quantity() << ' ' << candies.get_cost() << '\n';
	std::cout << carrots.get_quantity() << ' ' << carrots.get_cost() << '\n';
	Order check;
	check.add_position(candies);
	check.add_position(carrots);
	WeightPosition car(carr, 41.5);
	check.add_position(car);
	check.get_info();
	Client Rus;
	Rus.earn_money(150);
	std::cout<<Rus.pay_and_recieve_order(check);
	std::cout << check.empty();*/
	Order order;
	if (order.empty())
	{
		std::cout << "Пустой!\n";
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
	std::cout << "Заказ пуст? " << order.empty() << '\n';
	return 0;
}