#include"Product.h"
class Position {
public:
	Position(std::unique_ptr<Product> ptr_product) : m_ptr_product(std::move(ptr_product)) {}
	std::unique_ptr<Product>& get_ptr_product() {
		return m_ptr_product;
	}
	virtual double get_cost() = 0;
	virtual double get_quantity() = 0;
protected:
	std::unique_ptr<Product> m_ptr_product;
};

class AmountPosition : public Position {
public:
	AmountPosition(std::unique_ptr<AmountProduct> ptr_product, const size_t& amount):Position(std::move(ptr_product)), m_amount(amount) {}
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
	WeightPosition(std::unique_ptr<WeightProduct> ptr_product, const double& weight) :Position(std::move(ptr_product)), m_weight(weight) {}
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
