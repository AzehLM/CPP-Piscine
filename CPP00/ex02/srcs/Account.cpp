#include <iostream>
#include <iomanip>
#include <ctime>

#include "Account.hpp"

int	Account:: _nbAccounts = 0;
int	Account:: _totalAmount = 0;
int	Account:: _totalNbDeposits = 0;
int	Account:: _totalNbWithdrawals = 0;

int	Account::getNbAccounts(void)
{
	return (_nbAccounts);
}

int	Account::getTotalAmount(void)
{
	return (_totalAmount);
}

int	Account::getNbDeposits(void)
{
	return (_totalNbDeposits);
}

int	Account::getNbWithdrawals(void)
{
	return (_totalNbWithdrawals);
}

void	Account::displayAccountsInfos(void)
{
	Account::_displayTimestamp();
	std::cout << "accounts:" << Account::getNbAccounts();
	std::cout << ";" << "total:" << Account::getTotalAmount();
	std::cout << ";" << "deposits:" << Account::getNbDeposits();
	std::cout << ";" << "withdrawals:" << Account::getNbWithdrawals() << std::endl;
}

Account::Account(int initial_deposit) : _accountIndex(Account::getNbAccounts()), _amount(initial_deposit), _nbDeposits(0), _nbWithdrawals(0)
{
	Account::_nbAccounts++;
	Account::_totalAmount += initial_deposit;

	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";" << "amount:" << this->_amount << ";created" << std::endl;
}

Account::~Account()
{
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex << ";" << "amount:" << this->checkAmount() << ";closed" << std::endl;
}

void	Account::_displayTimestamp(void)
{
	std::time_t	actual = std::time(NULL);
	std::tm*	local = std::localtime(&actual);

	std::cout << "[" << local->tm_year + 1900;
	std::cout << std::setw(2) << std::setfill('0') << local->tm_mon + 1;
	std::cout << std::setw(2) << std::setfill('0') << local->tm_mday << "_";
	std::cout << std::setw(2) << std::setfill('0') << local->tm_hour;
	std::cout << std::setw(2) << std::setfill('0') << local->tm_min;
	std::cout << std::setw(2) << std::setfill('0') << local->tm_sec << "] ";
}

void	Account::makeDeposit(int deposit)
{
	int	p_amount = this->checkAmount();
	this->_amount += deposit;
	this->_nbDeposits++;

	Account::_totalAmount += deposit;
	Account::_totalNbDeposits++;

	Account::_displayTimestamp();

	std::cout << "index:" << this->_accountIndex << ";p_amount:" << p_amount;
	std::cout << ";deposit:" << deposit << ";amount:" << this->_amount;
	std::cout << ";nb_deposits:" << this->_nbDeposits << std::endl;
}

int	Account::checkAmount(void) const
{
	return (this->_amount);
}


bool	Account::makeWithdrawal(int withdrawal)
{
	int	p_amount = this->checkAmount();
	bool isValidWithdrawal = !(withdrawal < 0 || withdrawal > this->_amount);
	Account::_displayTimestamp();
	if (!isValidWithdrawal)
	{
		std::cout << "index:" << this->_accountIndex << ";p_amount:" << checkAmount();
		std::cout << ";withdrawal:refused" << std::endl;
		return (false);
	}
	else
	{
		this->_amount -= withdrawal;
		this->_nbWithdrawals++;
		Account::_totalNbWithdrawals++;
		Account::_totalAmount -= withdrawal;
		std::cout << "index:" << this->_accountIndex << ";p_amount:" << p_amount;
		std::cout << ";withdrawal:" << withdrawal << ";amount:" << checkAmount();
		std::cout << ";nb_withdrawals:" << this->_nbWithdrawals << std::endl;
		return (true);
	}
}


void	Account::displayStatus(void) const
{
	Account::_displayTimestamp();

    std::cout << "index:" << this->_accountIndex << ";";
	std::cout << "amount:" << this->checkAmount() << ";";
	std::cout << "deposits:" << this->_nbDeposits << ";";
	std::cout << "withdrawals:" << this->_nbWithdrawals << std::endl;
}
