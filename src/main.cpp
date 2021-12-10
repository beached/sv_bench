// Copyright (c) Darrell Wright
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/beached/sv_bench
//

#include <daw/daw_string_view.h>

#include <benchmark/benchmark.h>
#include <string>

template<daw::string_view_bounds_type bounds_type>
intmax_t test( daw::basic_string_view<char, bounds_type> sv ) {
	benchmark::DoNotOptimize( sv );
	intmax_t result = 0;
	while( not sv.empty( ) ) {
		result += sv.front( );
		sv.remove_prefix( );
		benchmark::DoNotOptimize( sv );
	}
	return result;
}

std::string gen_data( ) {
	return std::string( 100'000'000ULL, 'a' );
}

static void TestPtrPtr( benchmark::State &state, std::string &&str ) {
	// Perform setup here
	for( auto _ : state ) {
		test<daw::string_view_bounds_type::pointer>( { str } );
		// This code gets timed
	}
}
BENCHMARK_CAPTURE( TestPtrPtr, TestPtrPtr, gen_data( ) );

static void TestPtrSizeT( benchmark::State &state, std::string &&str ) {
	// Perform setup here
	for( auto _ : state ) {
		test<daw::string_view_bounds_type::size>( { str } );
		// This code gets timed
	}
}
BENCHMARK_CAPTURE( TestPtrSizeT, TestPtrSizeT, gen_data( ) );

BENCHMARK_MAIN( );
