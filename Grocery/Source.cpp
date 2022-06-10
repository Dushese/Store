#include <iostream>
#include<locale.h>
#include"Position.h"
#include<vector>
#include<map>

class Order {
public:
	friend class Client;
	void add_position(Position* pos) {
		for (auto& ptr : m_ptr_positions)
		{
			if (ptr->get_ptr_product()->get_info() == pos->get_ptr_product()->get_info())
			{
				ptr = pos;
				return;
			}
		}
		m_ptr_positions.push_back(pos);
	}
	double get_cost()
	{
		double sum = 0;
		for (auto& ptr : m_ptr_positions)
		{
			sum += ptr->get_cost();
		}
		return sum;
	}
	void get_info()
	{
		if (empty())
		{
			std::cout << "\nТовары не выбраны\n";
		}
		else {
			for (auto& ptr : m_ptr_positions)
			{
				std::cout << ptr->get_ptr_product()->get_info() << '\n';
				std::cout << "\tКоличество:" << ptr->get_quantity() << '\n';
				std::cout << "\tЦена:" << ptr->get_cost() << '\n';
			}
			std::cout << "Итого:" << get_cost() << '\n';
		}
	}
	bool empty()
	{
		return m_ptr_positions.empty();
	}
private:
	void clear() { m_ptr_positions.clear(); }
	std::vector<Position*> m_ptr_positions;
};

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
	Client() :m_balance(Balance()) {}
	void earn_money(const double& money) { m_balance.add_money(money); }
	bool pay_and_recieve_order(Order& order)
	{
		if (m_balance.waste_money(order.get_cost()))
		{
			order.clear();
			std::cout << "\nЗаказ успешно оплачен!\n";
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

class PriceBase {
public:
	
	PriceBase(const PriceBase&) = delete; // конструктор копирования удалён
	PriceBase& operator = (const PriceBase&) = delete; // оператор = удалён
	static PriceBase& Instance() { // Использует отложенную инициализацию
		static PriceBase instance; // тут сработает дефолтный конструктор
		return instance;
	}
	WeightProduct get_product_weight_price(std::string name)
	{
		auto it = m_products_weight_price.find(name);
		if (it != m_products_weight_price.end())
		{
			return it->second;
		}
		else throw std::runtime_error("Такого продукта нет!!!\n");
	}
	AmountProduct get_product_amount_price(std::string name) {
		auto it = m_products_amount_price.find(name);
		if (it != m_products_amount_price.end())
		{
			return it->second;
		}
		else throw std::runtime_error("Такого продукта нет!!!\n");
	}
protected:
	PriceBase()
	{
		m_products_info = {
			 { "Apple", ProductInfo("Green sweet apple") },
			 { "Nuts", ProductInfo("Macadamia nut") },
			 { "Pensile", ProductInfo("Red pensile with rubber") },
			 { "Chair", ProductInfo("Wooden chair with armrests") },
						};
		m_products_weight_price = {
			 { "Apple", WeightProduct(m_products_info.at("Apple"), 11.3) },
			 { "Nuts", WeightProduct(m_products_info.at("Nuts"), 34.2) },
						};
		m_products_amount_price = {
			 { "Pensile", AmountProduct(m_products_info.at("Pensile"), 5.7) },
			 { "Chair", AmountProduct(m_products_info.at("Chair"), 75) },
						};
	}
private:
	std::map<std::string, ProductInfo> m_products_info;
	std::map<std::string, WeightProduct> m_products_weight_price;
	std::map<std::string, AmountProduct> m_products_amount_price;
};
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