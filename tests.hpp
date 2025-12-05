#ifndef TEST_H
#define TEST_H

/**
 * @brief lunches the basic transport problem given in the article
 * @param csv_path[in]  csv file where to save densities matrix ρ
 * @param json_path[in] json file where to save problem data
 */
void transport_test(const std::string &csv_path, const std::string &json_path);


/**
 * @brief lunches a basic diffusion problem with ρ0 = 2 + cos(2πx)
 * @param csv_path[in]  csv file where to save densities matrix ρ
 * @param json_path[in] json file where to save problem data
 */
void diffusion_test(const std::string &csv_path, const std::string &json_path);

#endif //TEST_H
