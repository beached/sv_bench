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
#include <string_view>

template<typename StringView>
intmax_t test( StringView sv ) {
	benchmark::DoNotOptimize( sv );
	intmax_t result = 0;
	while( not sv.empty( ) ) {
		result += sv.front( );
		sv.remove_prefix( 1 );
		benchmark::DoNotOptimize( sv );
	}
	benchmark::DoNotOptimize( result );
	return result;
}

template<typename StringView>
intmax_t test2( StringView sv ) {
	benchmark::DoNotOptimize( sv );
	intmax_t result = 0;
	for( std::size_t n = 0; n < sv.size( ); ++n ) {
		result += sv[n];
		benchmark::DoNotOptimize( sv );
	}
	benchmark::DoNotOptimize( result );
	return result;
}

std::string gen_data( ) {
	return std::string( 1'000'000'000ULL, 'a' );
}

static void TestRemovePrefixPtrPtr( benchmark::State &state, std::string &&str ) {
	for( auto _ : state ) {
		test<daw::string_view>( { str } );
	}
}
BENCHMARK_CAPTURE( TestRemovePrefixPtrPtr, TestRemovePrefixPtrPtr, gen_data( ) );

static void TestRemovePrefixPtrSizeT( benchmark::State &state, std::string &&str ) {
	for( auto _ : state ) {
		test<daw::basic_string_view<char, daw::string_view_bounds_type::size>>( { str } );
	}
}
BENCHMARK_CAPTURE( TestRemovePrefixPtrSizeT, TestRemovePrefixPtrSizeT, gen_data( ) );

static void TestRemovePrefixStdSV( benchmark::State &state, std::string &&str ) {
	for( auto _ : state ) {
		test<std::string_view>( std::string_view{ str } );
	}
}
BENCHMARK_CAPTURE( TestRemovePrefixStdSV, TestRemovePrefixStdSV, gen_data( ) );

static void TestSizePtrPtr( benchmark::State &state, std::string &&str ) {
	for( auto _ : state ) {
		test2<daw::string_view>( { str } );
	}
}
BENCHMARK_CAPTURE( TestSizePtrPtr, TestSizePtrPtr, gen_data( ) );

static void TestSizePtrSizeT( benchmark::State &state, std::string &&str ) {
	for( auto _ : state ) {
		test2<daw::basic_string_view<char, daw::string_view_bounds_type::size>>( { str } );
	}
}
BENCHMARK_CAPTURE( TestSizePtrSizeT, TestSizePtrSizeT, gen_data( ) );

static void TestSizeStdSV( benchmark::State &state, std::string &&str ) {
	for( auto _ : state ) {
		test2<std::string_view>( std::string_view{ str } );
	}
}
BENCHMARK_CAPTURE( TestSizeStdSV, TestSizeStdSV, gen_data( ) );

BENCHMARK_MAIN( );
