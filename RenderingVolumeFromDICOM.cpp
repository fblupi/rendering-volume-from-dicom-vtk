#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkDICOMImageReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>

int main(int argc, char *argv[]) {

  if (argc < 2) {
    cout << "Usage: " << argv[0] << " <dicom folder>" << endl;
    return EXIT_SUCCESS;
  }

	vtkSmartPointer<vtkImageData> imageData = vtkSmartPointer<vtkImageData>::New();
	vtkSmartPointer<vtkDICOMImageReader> reader = vtkSmartPointer<vtkDICOMImageReader>::New();
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> interactorStyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	vtkSmartPointer<vtkSmartVolumeMapper> volumeMapper = vtkSmartPointer<vtkSmartVolumeMapper>::New();
	vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
	vtkSmartPointer<vtkPiecewiseFunction> gradientOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
	vtkSmartPointer<vtkPiecewiseFunction> scalarOpacity = vtkSmartPointer<vtkPiecewiseFunction>::New();
	vtkSmartPointer<vtkColorTransferFunction> color = vtkSmartPointer<vtkColorTransferFunction>::New();
	vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();

	reader->SetDirectoryName(argv[1]);
	reader->Update();
	imageData->ShallowCopy(reader->GetOutput());

	renderer->SetBackground(0.1, 0.2, 0.3);

	renderWindow->AddRenderer(renderer);
	renderWindow->SetSize(500, 500);

	renderWindowInteractor->SetInteractorStyle(interactorStyle);
	renderWindowInteractor->SetRenderWindow(renderWindow);

	volumeMapper->SetBlendModeToComposite();
	volumeMapper->SetRequestedRenderModeToGPU();
	volumeMapper->SetInputData(imageData);

	volumeProperty->ShadeOn();
	volumeProperty->SetInterpolationTypeToLinear();

	volumeProperty->SetAmbient(0.1);
	volumeProperty->SetDiffuse(0.9);
	volumeProperty->SetSpecular(0.2);
	volumeProperty->SetSpecularPower(10.0);

	gradientOpacity->AddPoint(0.0, 0.0);
	gradientOpacity->AddPoint(2000.0, 1.0);
	volumeProperty->SetGradientOpacity(gradientOpacity);

	scalarOpacity->AddPoint(-800.0, 0.0);
	scalarOpacity->AddPoint(-750.0, 1.0);
	scalarOpacity->AddPoint(-350.0, 1.0);
	scalarOpacity->AddPoint(-300.0, 0.0);
	scalarOpacity->AddPoint(-200.0, 0.0);
	scalarOpacity->AddPoint(-100.0, 1.0);
	scalarOpacity->AddPoint(1000.0, 0.0);
	scalarOpacity->AddPoint(2750.0, 0.0);
	scalarOpacity->AddPoint(2976.0, 1.0);
	scalarOpacity->AddPoint(3000.0, 0.0);
	volumeProperty->SetScalarOpacity(scalarOpacity);

	color->AddRGBPoint(-750.0, 0.08, 0.05, 0.03);
	color->AddRGBPoint(-350.0, 0.39, 0.25, 0.16);
	color->AddRGBPoint(-200.0, 0.80, 0.80, 0.80);
	color->AddRGBPoint(2750.0, 0.70, 0.70, 0.70);
	color->AddRGBPoint(3000.0, 0.35, 0.35, 0.35);
	volumeProperty->SetColor(color);

	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);
	renderer->AddVolume(volume);
	renderer->ResetCamera();

	renderWindow->Render();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;

}
