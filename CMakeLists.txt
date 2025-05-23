cmake_minimum_required(VERSION 3.31)
project(marketplace)

set(CMAKE_CXX_STANDARD 26)

add_executable(marketplace main.cpp
        Book.cpp
        BundleDiscount.cpp
        Buyer.cpp
        Cache.cpp
        Clothing.cpp
        Electronics.cpp
        PercentageDiscount.cpp
        Product.cpp
        Search.cpp
        Seller.h
        Transactions.cpp
        Wallet.cpp
)
