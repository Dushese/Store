#pragma once
#include"Client.h"
#include<map>
class PriceBase {
public:

	PriceBase(const PriceBase&) = delete; // ����������� ����������� �����
	PriceBase& operator = (const PriceBase&) = delete; // �������� = �����
	static PriceBase& Instance() { // ���������� ���������� �������������
		static PriceBase instance; // ��� ��������� ��������� �����������
		return instance;
	}
	WeightProduct get_product_weight_price(std::string name);
	AmountProduct get_product_amount_price(std::string name);
protected:
	PriceBase();
private:
	std::map<std::string, ProductInfo> m_products_info;
	std::map<std::string, WeightProduct> m_products_weight_price;
	std::map<std::string, AmountProduct> m_products_amount_price;
};


WeightProduct PriceBase::get_product_weight_price(std::string name)
{
	auto it = m_products_weight_price.find(name);
	if (it != m_products_weight_price.end())
	{
		return it->second;
	}
	else throw std::runtime_error("������ �������� ���!!!\n");
}


AmountProduct PriceBase::get_product_amount_price(std::string name) {
	auto it = m_products_amount_price.find(name);
	if (it != m_products_amount_price.end())
	{
		return it->second;
	}
	else throw std::runtime_error("������ �������� ���!!!\n");
}

PriceBase::PriceBase()
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