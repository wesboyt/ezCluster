#include <cstdio>
#include <cstdlib>
#include <faiss/Clustering.h>
#include <faiss/IndexFlat.h>
#include <faiss/utils/distances.h>
#include <faiss/utils/random.h>
#include <iostream>
#include <vector>
#include <set>

std::vector<std::set<int>> cluster(std::vector<std::vector<float>> input, int clusters, int redos) {
    int dimension = input[0].size();
    int size = input.size();
    std::vector<float> conc;
    for(std::vector<float> datapoint : input) {
        conc.insert( conc.end(), datapoint.begin(), datapoint.end() );
    }
    faiss::ClusteringParameters params;
    params.nredo = redos;
    faiss::Clustering clus(dimension, clusters, params);
    std::unique_ptr<faiss::Index> index;
    index.reset(new faiss::IndexFlatL2(dimension));
    clus.train(size, conc.data(), *index.get());
    std::cout << index->ntotal << std::endl;

    std::vector<float> dis(size);
    std::vector<faiss::idx_t> idx(size);

    index->search(size, conc.data(), clusters, dis.data(), idx.data());
    std::vector<std::set<int>> result;
    return result;
}
