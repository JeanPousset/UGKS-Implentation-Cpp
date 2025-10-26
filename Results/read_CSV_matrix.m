function dataMatrix = read_CSV_matrix(csv_name)
    %   Input:
    %       csv_name - The name of the CSV file (string).
    %
    %   Output:
    %       dataMatrix - A matrix containing the data from the CSV file.
    %
  
    % This function automatically handles the conversion to a numeric matrix
    dataMatrix = readmatrix(csv_name);

    fprintf('CSV file "%s" successfully read as a matrix.\n', csv_name);
end