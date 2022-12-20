#from draw_graphs import draw_graphs
from pysat.solvers import Glucose4 as slv

from timeit import default_timer as timer

from pysat.card import EncType, CardEnc

def reduce_vc2sat(graph, k):
    cnf_form = [[i + 1, j + 1] for i in range(len(graph)) for j in range(i + 1, len(graph[i])) if graph[i][j] == 1]

    nodes = list(range(1, len(graph) + 1))
    cnf_form = cnf_form + CardEnc.atmost(nodes, k, EncType.sortnetwrk).clauses
    return cnf_form


def answer_sat(graph, k, find_all_solutions):
    cnf_form = reduce_vc2sat(graph, k)

    solver = slv()

    solver.append_formula(cnf_form)

    if solver.solve():
        if find_all_solutions:
            solutions = []
            while solver.solve():
               # -*- coding: utf-8 -*- print("OK" if solutions.count(solver.get_model) == 0 else "!!!!!!!!!")
                solutions.append(solver.get_model())
                cnf_form.append([-lit for lit in solver.get_model()])
                solver.append_formula(cnf_form)
            return True, solutions
        else:
            return True, solver.get_model()
    else:
        return False, None


def binary_search(graph, low, high, find_all_solutions):
    if low == 0 and high == 0:
        return 0, []

    if low == high:
        has_solution, solution = answer_sat(graph, low, find_all_solutions)
        if has_solution:
            return low, solution

    mid = (low + high) // 2

    has_solution, _ = answer_sat(graph, mid, False)

    if not has_solution:
        return binary_search(graph, mid + 1, high, find_all_solutions)
    else:
        return binary_search(graph, low, mid, find_all_solutions)


def cover_2(graph):
    vc = [0] * len(graph)
    for i in range(len(graph)):
        for j in range(i + 1, len(graph)):
            if graph[i][j] and not vc[i] and not vc[j]:
                vc[i] = 1
                vc[j] = 1

                if is_cover_right(graph, vc):
                    return sum(vc)
    return sum(vc)


def greedy(graph):
    vc = [0] * len(graph)
    degree_list = [(sum(graph[i]), i) for i in range(len(graph))]
    sorted_indexes = [index for _, index in sorted(degree_list, reverse=True)]
    for i in sorted_indexes:
        if is_cover_right(graph, vc):
            break

        vc[i] = 1

    return sum(vc)


def is_cover_right(graph, cover):
    # Check if the vertex cover covers all the edges in the graph.
    for i in range(len(graph)):
        for j in range(i + 1, len(graph[i])):
            if graph[i][j] == 1 and cover[i] == 0 and cover[j] == 0:
                return False
    # If the vertex cover passes the check, return True.
    return True


def are_covers_right(graph, covers):
    for cover in covers:
        if not is_cover_right(graph, cover):
            return False
    return True


def test(filename, all_solutions):
    import pickle
    with open(filename, 'rb') as f:
        data = pickle.load(f)

    for graph in data:
        answer = binary_search(graph, 1, len(graph), all_solutions)
        if is_cover_right(graph, answer[1]):
            print("\nMinimum Vertex Cover has: " + str(answer[0]) + " nodes")
            print("SAT-solver's all possible answers are: " + str(answer[1][0:len(graph)]))
           # draw_graphs(graph, answer[1])

            # for x in answer[1]:
            #     #+ str(answer[1][0:len(graph)]))
            #     print(x)
        else:
            print("SOLUTION INCORRECT!")


def test_approximation(filename, all_solutions):
    import pickle
    with open(filename, 'rb') as f:
        data = pickle.load(f)

    for graph in data:
        c1 = cover_2(graph)
        c2 = greedy(graph)

        i = max(c1, c2) // 2
        j = min(c1, c2)

        answer = binary_search(graph, i, j, all_solutions)

        if is_cover_right(graph, answer[1][0:len(graph)]):
            print("\nMinimum Vertex Cover has: " + str(answer[0]) + " nodes")
            print("SAT-solver's answer is: " + str(answer[1][0:len(graph)]))
           # draw_graphs(graph, answer[1])
        else:
            print("SOLUTION INCORRECT!")


def test_all_solutions(filename, all_solutions):
    import pickle
    with open(filename, 'rb') as f:
        data = pickle.load(f)

    for graph in data:
        answer = binary_search(graph, 1, len(graph), all_solutions)

        covers = [cover[0:len(graph)] for cover in answer[1]]
        if are_covers_right(graph, answer[1]):
            print("\nMinimum Vertex Cover has: " + str(answer[0]) + " nodes\n" + "SAT-solver's answer is:\nCover num="
                    + str(len(covers)))
        else:
            print("SOLUTION INCORRECT!")

        #draw_graphs(graph, answer[1])


if __name__ == "__main__":
    # Simple default cases, to check it works fine
    """ start = timer()
    test('mydata/data1.pkl', False)
    end = timer()
    print('Elapsed time: ' + str(end - start) + ' seconds')
 """
    # # Simple default cases with approximation
    # start = timer()
    # test_approximation('mydata/data1.pkl', False)
    # end = timer()
    # print('Elapsed time: ' + str(end - start) + ' seconds')
    #
    # # More complex cases, to check efficiency
    # start = timer()
    # test('mydata/data2.pkl', False)
    # end = timer()
    # print('Elapsed time: ' + str(end - start) + ' seconds')
    #
    # # Cases to test APPROXIMATION algorithms
    # start = timer()
    # test_approximation('mydata/data2.pkl', False)
    # end = timer()
    # print('Elapsed time: ' + str(end - start) + ' seconds')

    # Find ALL possible solutions
    start = timer()
    test_all_solutions('mydata/data1.pkl', True)
    end = timer()
    print('Elapsed time: ' + str(end - start) + ' seconds')