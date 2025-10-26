function [data] = read_json(json_name)

    % Read json file
    fid = fopen(json_name, 'r');
    raw = fread(fid, inf);
    str = char(raw');
    fclose(fid);
    
    % Decode json into a matlab structure
    data = jsondecode(str);

    fprintf('json file "%s" successfully read as a matrix.\n', json_name);

end