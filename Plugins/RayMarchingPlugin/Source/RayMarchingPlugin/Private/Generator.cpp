// Fill out your copyright notice in the Description page of Project Settings.


#include "Generator.h"
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>


// Sets default values
AGenerator::AGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AGenerator::DoSomething()
{
	std::string OutputFile = "";

	std::string curDir = TCHAR_TO_UTF8(*(FPaths::GameSourceDir() + TEXT("../Plugins/RayMarchingPlugin/Shaders/")));

	std::ifstream fin(curDir + "SDFractalLibrary.ush");
	std::string filename = "../../Shaders/SDFractalLibrary.ush";

	const std::string FractalCodeInsert = "// --FRACTAL-CODE-INSERT--";
	const std::string DistInsert = "// --DIST-INSERT--";
	const std::string NormalInsert = "// --NORMAL-INSERT--";
	std::string SDFBegin = "// --SDF--";
	SDFBegin += std::string(TCHAR_TO_UTF8(*Name));
	SDFBegin += "--BEGIN--";

	std::string SDFEnd= "// --SDF--";
	SDFEnd += std::string(TCHAR_TO_UTF8(*Name));
	SDFEnd += "--END--";

	std::string DistBegin = "// --DIST--";
	DistBegin += std::string(TCHAR_TO_UTF8(*Name));
	DistBegin += "--BEGIN--";

	std::string DistEnd = "// --DIST--";
	DistEnd += std::string(TCHAR_TO_UTF8(*Name));
	DistEnd += "--END--";

	std::string NormalBegin = "// --NORMAL--";
	NormalBegin += std::string(TCHAR_TO_UTF8(*Name));
	NormalBegin += "--BEGIN--";

	std::string NormalEnd= "// --NORMAL--";
	NormalEnd += std::string(TCHAR_TO_UTF8(*Name));
	NormalEnd += "--END--";

	bool DoesAlreadyExist = false;
	bool DoesInsertSDTypeOutput = false;
	bool DoesInsertNormalTypeOutput = false;
	bool DoesInsertOutput = false;
	std::string current;
	while(getline(fin, current))
	{
		if (DoesInsertSDTypeOutput)
		{
			if (current.find(DistEnd) != std::string::npos)
			{
				DoesInsertSDTypeOutput = false;
				OutputFile += DistEnd;
				OutputFile += "\n";
			}

			continue;
		}

		if (DoesInsertNormalTypeOutput)
		{
			if (current.find(NormalEnd) != std::string::npos)
			{
				DoesInsertNormalTypeOutput = false;
				OutputFile += NormalEnd;
				OutputFile += "\n";
			}

			continue;
		}

		if (DoesInsertOutput)
		{
			if (current.find(SDFEnd) != std::string::npos)
			{
				DoesInsertOutput = false;
				OutputFile += SDFEnd;
				OutputFile += "\n";
			}

			continue;
		}

		if (current.find(DistBegin) != std::string::npos)
		{
			DoesAlreadyExist = true;
			DoesInsertSDTypeOutput = true;
			OutputFile += DistBegin + "\n";
			OutputFile += TCHAR_TO_UTF8(*SDTypeOutput);
			OutputFile += "\n";
			continue;
		}
		else if (!DoesAlreadyExist && current.find(DistInsert) != std::string::npos)
		{
			OutputFile += DistBegin + "\n";
			OutputFile += TCHAR_TO_UTF8(*SDTypeOutput);
			OutputFile += "\n";
			OutputFile += DistEnd + "\n";
			OutputFile += DistInsert + "\n";

			continue;
		}

		if (current.find(NormalBegin) != std::string::npos)
		{
			DoesAlreadyExist = true;
			DoesInsertNormalTypeOutput = true;
			OutputFile += NormalBegin + "\n";
			OutputFile += TCHAR_TO_UTF8(*NormalTypeOutput);
			OutputFile += "\n";
			continue;
		}
		else if (!DoesAlreadyExist && current.find(NormalInsert) != std::string::npos)
		{
			OutputFile += NormalBegin + "\n";
			OutputFile += TCHAR_TO_UTF8(*NormalTypeOutput);
			OutputFile += "\n";
			OutputFile += NormalEnd + "\n";
			OutputFile += NormalInsert + "\n";

			continue;
		}

		if (current.find(SDFBegin) != std::string::npos)
		{
			DoesAlreadyExist = true;
			DoesInsertOutput = true;
			OutputFile += SDFBegin + "\n";
			OutputFile += TCHAR_TO_UTF8(*OutputString);
			OutputFile += "\n";
			continue;
		}
		else if (!DoesAlreadyExist && current.find(FractalCodeInsert) != std::string::npos)
		{
			OutputFile += SDFBegin + "\n";
			OutputFile += TCHAR_TO_UTF8(*OutputString);
			OutputFile += "\n";
			OutputFile += SDFEnd + "\n";
			OutputFile += FractalCodeInsert + "\n";

			continue;
		}

		OutputFile += current + "\n";
	}

	std::ofstream fout(curDir + "SDFractalLibrary.ush");
	fout << OutputFile;

	float a = 3;
}

