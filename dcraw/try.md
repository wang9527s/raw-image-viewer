// https://github.com/ncruces/dcraw/releases

```bash
# 使用如下命令，结果差异更加明显。生成的tiff亮度很低
.\dcraw.exe -w -a -o 1 -q 3 -4 -T E:\test.ARW
.\dcraw.exe -w -a -o 1 -q 3 -4 -T -r 1.0 1.0 1.0 1.0 E:\test.ARW

# 过于明亮
dcraw -w -T test.ARW
```