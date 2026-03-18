from collections import Counter
from collections import defaultdict

def suspiciousness_basic_frequency(input_dict):
    """
    Takes a dictionary with string keys (test names) and a list of tuples. The first tuple element is method that is executed prior to test/assertion failure and the next tuple element is the weight of method, depending on proximity to the failed assertion 
    dict[str, list[tuple[str, int]]]
    Returns the list of all methods that were executed by the failed tests before assertion, sorted by their frequency of appearance (descending).
    """
    # Flatten all values into a single list
    all_executed_methods = []
    for executed_methods in input_dict.values():
        for executed_method, _ in executed_methods:
            all_executed_methods.append(executed_method)

    # Count frequency of each value
    freq_counter = Counter(all_executed_methods)

    # Sort values by frequency (descending), then alphabetically for tie-break
    suspicious_methods = sorted(freq_counter.items(), key=lambda x: (-x[1], x[0]))

    # Print each value and its frequency
    print("Reqeuncy-based ranking")
    for methods, freqs in suspicious_methods:
        print(f"{methods}: {freqs}")

    return suspicious_methods

def suspiciousness_weighted_descending(input_dict,order):
    """
    Takes a dictionary with string keys (test names) and a list of tuples. The first tuple element is method that is executed prior to test/assertion failure and the next tuple element is the weight of method, depending on proximity to the failed assertion 
    dict[str, list[tuple[str, int]]]
    Returns the list of all methods that were executed by the failed tests before assertion, sorted by their aggregated weights (descending).
    """
    weight_map = defaultdict(int)

    # Aggregate weights
    for executed_methods in input_dict.values():
        for executed_method, weight in executed_methods:
            weight_map[executed_method] += weight

    if order == 'ascending':
        # Sort by total weight descending, then alphabetically
        suspicious_methods = sorted(weight_map.items(), key=lambda x: (x[1], x[0]))
        # Print result
        print("Weight-based ranking ascending")
        for method, total_weight in suspicious_methods:
            print(f"{method}: {total_weight}")
    else:
        # Sort by total weight descending, then alphabetically
        suspicious_methods = sorted(weight_map.items(), key=lambda x: (-x[1], x[0]))
        # Print result
        print("Weight-based ranking descending")
        for method, total_weight in suspicious_methods:
            print(f"{method}: {total_weight}")

    return suspicious_methods


input_data = {
    "test1": [("m1", 1), ("m2", 2), ("m4", 3)],
    "test2": [("m2", 1), ("m1", 1)],
    "test3": [("m5", 4), ("m1", 2), ("m3", 1)]
}

result_basic = suspiciousness_basic_frequency(input_data)
result_weighted_ascending = suspiciousness_weighted_descending(input_data,"ascending")
result_weighted_descending = suspiciousness_weighted_descending(input_data,"descending")
