#pragma once
#include"Position.h"
#include<vector>
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