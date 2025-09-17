# NURBS建模示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例展示 AMCAX NURBS 模组中的一些主要建模功能。具体实现如下：

### 1. 构建左侧管道

	1. 使用 AMCAX::Geom3Ellipse 创建一个椭圆
	
	2. 使用 Translate() 方法对椭圆进行了平移操作
	
	3. 使用 std::vector<AMCAX::Point3> 定义一个名为 sectionPoles 的向量
	
	4. 使用 AMCAX::NURBSAPIBuildCurve::BuildCurve 创建一个 B 样条曲线
	
	5. 使用 std::shared_ptr<AMCAX::Geom3BSplineCurve> 定义一个名为 endingProfileCurve 的共享指针，存储 B 样条曲线
	
	6. 使用 std::vector<AMCAX::Point3> 定义一个名为 guidePoles 的向量
	
	7. 使用 AMCAX::NURBSAPIBuildCurve::BuildCurve 创建一个 B 样条曲线
	
	8. 使用 std::shared_ptr<AMCAX::Geom3BSplineCurve> 定义一个名为 guide 的共享指针，存储 B 样条曲线
	
	9. 使用 std::vector<std::pair<int, double>> 定义向量 guideCorrParams
	
	10. 使用 std::vector<AMCAX::NURBSCurveSection> 定义向量 profiles
	
	11. 使用 AMCAX::NURBSAPISweep::SweepOneRail 执行沿着脊柱扫一个侧面
	
	12. 获取曲面，并存储在 complexPipe 中
	
	13. 使用 AMCAX::STEP::STEPWriter 将 TopoShape 对象转换为 STEP 文件
	
	14. 使用 AMCAX::STEP::STEPWriter 下的 Init() 将 STEP 文件的头部分写入流
	
	15. 使用 AMCAX::MakeFace 下的 MakeFace() 将 Geom3BSplineSurface 转换成 TopoShape
	
	16. 使用 AMCAX::STEP::STEPWriter 下的 WriteShape() 写入STEP文件的数据部分
	
	17. 使用 AMCAX::STEP::STEPWriter 下的 Done() 编写 STEP 文件的结束部分，关闭输出文件


​	

<div align = center><img src="https://s2.loli.net/2024/06/11/12LFs57qNradIBT.png" width="600" height="300">

