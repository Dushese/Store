#pragma once
#include"Position.h"
#include<vector>
class Order {
public:
	friend class Client;
	void add_position(std::unique_ptr<Position> ptr_pos);
	double get_cost() const;
	void get_info()const;
	bool empty()const
	{
		return m_ptr_positions.empty();
	}
private:
	void clear() { m_ptr_positions.clear(); }
	std::vector<std::unique_ptr<Position>> m_ptr_positions;
};

void Order::add_position(std::unique_ptr<Position> ptr_pos) {
	for (auto& pos : m_ptr_positions)
	{
		if (ptr_pos->get_ptr_product()->get_info() == pos->get_ptr_product()->get_info())
		{
			pos = std::move(ptr_pos);
			return;
		}
	}
	m_ptr_positions.push_back(std::move(ptr_pos));
}
double Order::get_cost()const
{

	double sum = 0;
	for (auto& ptr : m_ptr_positions)
	{
		sum += ptr->get_cost();
	}
	return sum;
}

void Order::get_info()const
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