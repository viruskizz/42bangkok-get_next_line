## Presudo code

### Start
1. Declare `file` type if not existed at start
2. check `fd` is valid greater than 0
3. check `file` has declared if not declare and initial value
4. check `file.is_end == -1` has closed yet.
5. if `file.is_end == 0` file don't have next line go to read next buffer
6. if `file.is_end == 1` file have next line return `file.line`