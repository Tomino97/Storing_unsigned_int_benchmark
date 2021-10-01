#include <vector>
#include <ctime>
#include <algorithm>

namespace ubench {
    struct result {
        long ci_low, mean, ci_high; /* ci = confidence interval */
    };

    std::ostream &operator<<(std::ostream &output, const result &r) {
        output << r.ci_low << " " << r.mean << " " << r.ci_high << std::endl;
        return output;
    }

    struct bootstrap {
        std::vector<long> data;

        void add_sample(long value) {
            data.emplace_back(value);
        }; /* register a single data point */

        void clear() {
            data.clear();
        }; /* remove all data */

        result process(int iterations) {
            std::vector<long> samples;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distrib(0, data.size() - 1);

            for (int i = 0; i < iterations; i++) {
                long long sum = 0;
                for (unsigned int j = 0; j < data.size(); j++) {
                    sum += data[distrib(gen)];
                }
                samples.emplace_back(sum / data.size());
            }
            std::sort(samples.begin(), samples.end());

            result output = {0, 0, 0};
            output.ci_low = samples[samples.size() * 0.05];
            output.mean = samples[samples.size() * 0.5];
            output.ci_high = samples[samples.size() * 0.95];
            return output;
        }; /* do the bootstrapping (non-destructively) */
    };

    result measure(void (*f)(), int rep_min = 10,
                   int rep_max = 1000, int timeout = 3000000) {
        /* Repeatedly invoke function 'f', measuring its runtime.
         * The `rep_*` specify the minimum and the maximum number of
         * repetitions, and `timeout` specifies how many
         * microseconds of runtime to accumulate.  See `spec.txt`
         * for details. */
        struct timespec start, end;
        struct bootstrap data;
        long totalTime = 0;
        int iterations = 0;
        while (iterations < rep_min || (totalTime < timeout && iterations < rep_max)) {
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
            f();
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
            long duration = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
            data.add_sample(duration);
            totalTime += duration;
            iterations++;
        }
        return data.process(10000);
    }
}

