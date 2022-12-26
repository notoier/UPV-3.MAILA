import networkx as nx
import matplotlib.pyplot as plt


def draw_graph(graph, cover):
    color_map = ['green' if elem>0 else 'blue' for elem in cover[0:len(graph)]]

    G = nx.Graph()
    G.add_nodes_from(range(len(graph)))
    for i in range(len(graph)):
        for j in range(i+1, len(graph)):
            if graph[i][j]==1:
                G.add_edge(i,j,weight=0.1)
                
    nx.draw_shell(G, node_color=color_map, with_labels = True)
    plt.show()
    plt.clf()


def draw_graphs(graph, answer):
    if type(answer[1]) == list:
        None
        for cover in answer[1]:
            draw_graph(graph, cover)
    else:
        draw_graph(graph, answer)
