# NURBS建模示例

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### 该示例展示 AMCAX NURBS 模组中的一些主要建模功能。具体实现如下：

### 2. 构建右侧圆形截面管道

	1. 使用 std::vector<AMCAX::Point3> 定义向量 centerCurvePoles
	
	2. 使用 std::shared_ptr<AMCAX::Geom3BSplineCurve> 定义指针 centerCurve
	
	3. 使用 AMCAX::NURBSAPIBuildCurve::BuildCurve 建立 NURBS 曲线
	
	4. 使用 std::shared_ptr<AMCAX::Geom3BSplineCurve> 定义 spine 指针
	
	5. 使用 AMCAX::Geom3BSplineCurve 下的 FirstParameter() 与 LastParameter() 获取脊柱曲线的参数范围
	
	6. 使用 AMCAX::LawConstant 创建一个对象 radiusLaw
	
	7. 使用 AMCAX::LawConstant 下的 Set() 设置参数
	
	8. 使用 AMCAX::NURBSAPICircularSweep 下的 SweepWithCenterAndRadius() 对由中心曲线和半径定义的圆形轮廓进行扫掠
	
	9. 扫描的结果存储在 circlePipe 中，同时返回一个状态
	
	10. 使用 AMCAX::STEP::STEPWriter 将 TopoShape 对象转换为 STEP 文件
	
	11. 使用 AMCAX::STEP::STEPWriter 下的 Init() 将 STEP 文件的头部分写入流
	
	12. 使用 AMCAX::MakeFace 下的 MakeFace() 将 Geom3BSplineSurface 转换成 TopoShape
	
	13. 使用 AMCAX::STEP::STEPWriter 下的 WriteShape() 写入STEP文件的数据部分
	
	14. 使用 AMCAX::STEP::STEPWriter 下的 Done() 编写 STEP 文件的结束部分，关闭输出文件


<div align = center><img src="https://s2.loli.net/2024/06/11/lvyrE4oDGNc8ZFa.png" width="600" height="300">

