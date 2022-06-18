#pragma once
#include <string>
#include<iostream>
#include<sstream>

class ProductInfo {
public:
	ProductInfo(const std::string& info) : m_info(info){}
	const std::string& get_info()const
	{
		return m_info;
	}
private:
	std::string m_info;
};

class Product {
public:
	Product(ProductInfo& inf) : m_product_info(inf) {}
	virtual std::string get_info() const = 0;
	virtual double get_cost() const = 0;
protected:
	ProductInfo& m_product_info;
};

class WeightProduct : public Product
{
public:
	WeightProduct(ProductInfo& inf, double cost) : Product(inf), m_cost_per_kg(cost) {}
	std::string get_info() const override
	{
		std::ostringstream strs;
		strs << m_cost_per_kg;
		std::string str = std::string(m_product_info.get_info() + ": " + strs.str() + " деняк за килограмм ");
		return str;
	}
	double get_cost() const override
	{
		return m_cost_per_kg;
	}
private:
	double m_cost_per_kg;
};

class AmountProduct : public Product
{
public:
	AmountProduct(ProductInfo& inf, const double& cost) : Product(inf), m_cost_per_one(cost) {}
	std::string get_info()const override
	{
		std::ostringstream strs;
		strs << m_cost_per_one;
		std::string str = m_product_info.get_info() + ": " + strs.str() + " деняк за одну шт ";
		return str;
	}
	double get_cost()const  override
	{
		return m_cost_per_one;
	}
private:
	double m_cost_per_one;
};
