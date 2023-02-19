#include <cstdio>
#include <cstdlib>
#include <faiss/Clustering.h>
#include <faiss/IndexFlat.h>
#include <faiss/utils/distances.h>
#include <faiss/utils/random.h>
#include <iostream>
#include <vector>
#include <set>

std::vector<std::vector<int>> cluster(std::vector<std::vector<float>> input, int numClusters, int retry) {
    int dimensions = input[0].size();
    int size = input.size();
    std::vector<float> conc;
    for(std::vector<float> datapoint : input) {
        conc.insert( conc.end(), datapoint.begin(), datapoint.end());
    }
    faiss::ClusteringParameters params;
    params.nredo = retry;
    faiss::Clustering clus(dimensions, numClusters, params);
    std::unique_ptr<faiss::Index> index;
    index.reset(new faiss::IndexFlatL2(dimensions));
    clus.train(size, conc.data(), *index.get());
    std::cout << index->ntotal << std::endl;

    faiss::IndexFlatL2 cIndex(dimensions);
    std::vector<float> dis(size);
    std::vector<faiss::idx_t> idx(size);
    
    cIndex.add(numClusters, clus.centroids.data());
    cIndex.search(size, conc.data(), 1, dis.data(), idx.data());

    std::vector<std::vector<int>> result;
    for(int i = 0; i < numClusters; i++) {
        result.emplace_back(std::vector<int>());
    }
    for(int i = 0; i < size; i++) {
        result[idx[i]].emplace_back(i);
    }
    return result;
}
