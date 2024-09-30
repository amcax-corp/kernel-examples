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

### 3. 构建中间过渡曲面

	1. 使用 std::vector<double> 定义向量 parameters1 , parameters2 , tol
	
	2. 使用 std::shared_ptr<AMCAX::Geom3BSplineSurface> 定义指针 blendSurface
	
	3. 使用 AMCAX::NURBSAPIBlend 下的 BlendSurfaces() 构造一个连接两个表面的混合表面
	
	4. 使用 AMCAX::ContinuityType 设置连续性的类型
	
	5. 使用 AMCAX::NURBSAPIBlend 下的 BlendSurfaces() 构造一个连接两个表面的混合表面 blendSurface 

### 4. 生成 step 文件
	
	1. 使用 AMCAX::MakeFace 下的 MakeFace() 将 Geom3BSplineSurface 转换成 TopoShape
	
	2. 使用 AMCAX::BoolBRepFuse 下的 BoolBRepFuse() 执行布尔融合操作，将三个形状合并成一个
	
	3. 使用 AMCAX::STEP::StepWriter 将 TopoShape 对象转换为 STEP 文件
	
	4. 使用 AMCAX::STEP::StepWriter 下的 Init() 将 STEP 文件的头部分写入流
	
	5. 使用 AMCAX::STEP::StepWriter 下的 WriteShape() 写入STEP文件的数据部分
	
	6. 使用 AMCAX::STEP::StepWriter 下的 Done() 编写 STEP 文件的结束部分，关闭输出文件
	


<div align = center><img src="https://s2.loli.net/2024/06/28/2LlvhGrIe6pqbsg.png" width="600" height="300">
