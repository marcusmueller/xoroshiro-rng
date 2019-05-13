// Examples and test
// This file is under GPLv3.
// Copyright (and left) Marcus Müller

#include "xoroshiro128p.hpp"
#include <iostream>
#include <random>

int main(int argc, char **argv) {
  double p = 0.3;
  unsigned int count = 1UL << 30;
  unsigned int counter;

  auto gen = rng::xoroshiro128p();
  auto gen2 = std::mt19937();

  std::cout << "=== XOROSHIRO128+ ===\n";
  std::binomial_distribution<rng::xoroshiro128p::result_type> binom(1, p);
  counter = 0;
  for (unsigned int i = 0; i < count; ++i) {
    if (binom(gen))
      ++counter;
  }
  std::cout << " " << count << " attempts\n " << counter << " true\n "
            << (double)counter / count << " relative freq\n " << p << " p\n "
            << std::scientific << p - (double)counter / count << " p-freq\n";

  std::cout << "=== MT19937 ===\n";
  std::binomial_distribution<> binom2(1, p);
  counter = 0;
  for (unsigned int i = 0; i < count; ++i) {
    if (binom2(gen2))
      ++counter;
  }
  std::cout << " " << count << " attempts\n " << counter << " true\n "
            << (double)counter / count << " relative freq\n " << p << " p\n "
            << std::scientific << p - (double)counter / count << " p-freq\n";

  std::cout << "=== XOROSHIRO128+ naive p ===\n";
  counter = 0;
  rng::xoroshiro128p::result_type threshold = p * gen.max();
  std::cout << " " << threshold << " threshold\n";
  for (unsigned int i = 0; i < count; ++i) {
    if (gen() <= threshold)
      ++counter;
  }
  std::cout << " " << count << " attempts\n " << counter << " true\n "
            << (double)counter / count << " relative freq\n " << p << " p\n "
            << std::scientific << p - (double)counter / count << " p-freq\n";
}
