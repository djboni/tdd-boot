TESTS_FRAMEWORKS = unity cpputest cmocka boosttest

all:
	for Framework in $(TESTS_FRAMEWORKS); do \
		( \
			cd $$Framework; \
			./scripts/run_test.sh --all || \
				break; \
		) \
	done

clean:
	for Framework in $(TESTS_FRAMEWORKS); do \
		( \
			cd $$Framework; \
			./scripts/run_test.sh --clean || \
				break; \
		) \
	done
