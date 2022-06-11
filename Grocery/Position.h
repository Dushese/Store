#include"Product.h"
class Position {
public:
	Position(Product& product) : m_ptr_product(&product) {}
	Product* get_ptr_product() {
		return m_ptr_product;
	}
	virtual double get_cost() = 0;
	virtual double get_quantity() = 0;
protected:
	Product* m_ptr_product;
};

class AmountPosition : public Position {
public:
	AmountPosition(AmountProduct& product, const size_t& amount) :Position(product), m_amount(amount) {}
	double get_cost() override
	{
		return m_ptr_product->get_cost() * m_amount;
	}
	double get_quantity() override {
		return m_amount;
	}
private:
	size_t m_amount;
};

class WeightPosition : public Position {
public:
	WeightPosition(WeightProduct& product, const double& weight) :Position(product), m_weight(weight) {}
	double get_cost() override
	{
		return m_ptr_product->get_cost() * m_weight;
	}
	double get_quantity() override {
		return m_weight;
	}
private:
	double m_weight;
};
