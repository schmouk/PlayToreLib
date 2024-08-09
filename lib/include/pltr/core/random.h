#pragma once

/*
    GNU GENERAL PUBLIC LICENSE
    Version 3, 29 June 2007

    This is part of library PlayToreLib, a c++ generic library for coding games applications.

    Copyright (C) 2024 Philippe Schmouker, ph.schmouker (at) gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

//===========================================================================
#include <cstdint>
#include <mutex>
#include <random>
#include <type_traits>


//===========================================================================
namespace pltr::core
{
    //=======================================================================
    // \brief  The base class for all pseudo random numbers generator, whatever the distribution function used. */
    class BaseRandom
    {
    public:
        inline BaseRandom() noexcept = default;     //!< default empty constructor.

        BaseRandom(const BaseRandom&) = delete;     //!< no copy construction allowed.
        BaseRandom(BaseRandom&&) = delete;          //!< no move construction allowed.

        virtual ~BaseRandom() noexcept = default;   //!< default destructor.


    protected:
        static inline std::mt19937_64 _rand_generator{};
        static inline bool _already_inited{ false };

        inline void _check_init()
        {
            if (!_already_inited) {
                this->_rand_generator.seed(std::random_device()());
                this->_already_inited = true;
            }
        }

    };

    //=======================================================================
    /* \brief The class for pseudo random numbers generator that relate to a specified distribution function. */
    struct Random : protected BaseRandom
    {
    public:
        inline Random() noexcept = default;     //!< default empty constructor.

        virtual ~Random() noexcept = default;   //!< default destructor.

        template<typename DistributionFunctionT>
        inline const DistributionFunctionT::result_type operator() (DistributionFunctionT& distribution_function)  //!< returns a random number according to the specified distribution function
        {
            _check_init();
            return distribution_function(this->_rand_generator);
        }

        template<typename IntType>
            requires std::is_integral_v<IntType>
        inline const IntType urand(const IntType min, const IntType max)        //!< returns an random integer in range [min, max] with uniform distribution
        {
            _check_init();
            return std::uniform_int_distribution<IntType>(min, max)(this->_rand_generator);
        }

        template<typename FloatType>
            requires std::is_floating_point_v<FloatType>
        inline const FloatType urand(const FloatType min, const FloatType max)  //!< returns a random float value in range [min, max] with uniform distribution
        {
            _check_init();
            return std::uniform_real_distribution<FloatType>(min, max)(this->_rand_generator);
        }

        template<typename FloatType>
            requires std::is_floating_point_v<FloatType>
        inline const FloatType urand()                                          //!< returns a random float value in range [0.0, 1.0] with uniform distribution
        {
            _check_init();
            return std::uniform_real_distribution<FloatType>(FloatType(0), FloatType(1))(this->_rand_generator);
        }

        inline const double urand()                                             //!< shortcut to return a double value in range [0.0, 1.0] with uniform distribution
        {
            return urand<double>();
        }

    };


    //=======================================================================
    /* \brief The thread safe class for pseudo random numbers generator that relate to a specified distribution function. */
    class RandomThreadSafe : protected BaseRandom
    {
    public:
        inline RandomThreadSafe() noexcept = default;       //!< empty constructor.

        virtual ~RandomThreadSafe() noexcept = default;     //!< default destructor.

        template<typename DistributionFunctionT>
        inline const DistributionFunctionT::result_type operator() (DistributionFunctionT& distribution_function)
        {
            std::lock_guard<std::mutex> guard(this->_mutex);
            _check_init();
            return distribution_function(this->_rand_generator);
        }

        template<typename IntType>
            requires std::is_integral_v<IntType>
        inline const IntType urand(const IntType min, const IntType max)        //!< returns an random integer in range [min, max] with uniform distribution
        {
            std::lock_guard<std::mutex> guard(this->_mutex);
            _check_init();
            return std::uniform_int_distribution<IntType>(min, max)(this->_rand_generator);
        }

        template<typename FloatType>
            requires std::is_floating_point_v<FloatType>
        inline const FloatType urand(const FloatType min, const FloatType max)  //!< returns a random float value in range [min, max] with uniform distribution
        {
            std::lock_guard<std::mutex> guard(this->_mutex);
            _check_init();
            return std::uniform_real_distribution<FloatType>(min, max)(this->_rand_generator);
        }

        template<typename FloatType>
            requires std::is_floating_point_v<FloatType>
        inline const FloatType urand()                                          //!< returns a random float value in range [0.0, 1.0] with uniform distribution
        {
            _check_init();
            std::lock_guard<std::mutex> guard(this->_mutex);
            return std::uniform_real_distribution<FloatType>(FloatType(0), FloatType(1))(this->_rand_generator);
        }

        inline const double urand()                                             //!< shortcut to return a double value in range [0.0, 1.0] with uniform distribution
        {
            return urand<double>();
        }

    private:
        std::mutex _mutex;

    };

}