package main

import (
	"bufio"
	"fmt"
	"gopkg.in/yaml.v3"
	"io/fs"
	"os"
	"path/filepath"
	// "reflect"
	"strings"
)

type ImagesListType struct {
	Images struct {
		Testing []struct {
			Image string `yaml:"image"`
			Tag   string `yaml:"tag"`
		} `yaml:"testing"`
		Used []struct {
			Image string `yaml:"image"`
			Tag   string `yaml:"tag"`
		} `yaml:"used"`
	} `yaml:"images"`
}

var rootfolder_path string = "/Users/i323878/Desktop/AIF/"
var aicorefolder_path string = rootfolder_path + "aicore/"
var infrafolder_path string = rootfolder_path + "ai-infra-tooling/image_list.yml"
var target_file string = "component.yaml"
var aicore_component_info = make(map[string]string)
var imagelist ImagesListType

func gather_aicore_info(current_path string) {
	err := filepath.Walk(aicorefolder_path, func(path string, info fs.FileInfo, err error) error {
		current_path = path
		if err != nil {
			fmt.Printf("prevent panic by handling failure accessing a path %q: %v\n", path, err)
			return err
		}
		if !info.IsDir() && info.Name() == target_file {
			comp_dir_path := filepath.Dir(path)
			component_name := filepath.Base(comp_dir_path)
			version := "dummy"
			file, err := os.Open(current_path)
			if err != nil {
				return err
			}
			defer file.Close()

			sc := bufio.NewScanner(file)
			lines := make([]string, 0)

			// Read through 'tokens' until an EOF is encountered.
			for sc.Scan() {
				lines = append(lines, sc.Text())
			}
			for _, value := range lines {
				if strings.Contains(value, "version:") {
					// fmt.Printf("\n[" + value + "]")
					version = value
				}
			}
			if err := sc.Err(); err != nil {
				return err
			}
			aicore_component_info[component_name] = version
			return nil
		}
		return nil
	})
	if err != nil {
		fmt.Printf("error walking the path %q: %v\n", current_path, err)
		return
	}
}

func gather_infra_tooling_info(current_path string) {
	f, err := os.ReadFile(current_path)
	if err != nil {
		fmt.Printf("Error: %v\n", err)
		return
	}

	// Unmarshal our input YAML file into empty Car (var c)
	if err := yaml.Unmarshal(f, &imagelist); err != nil {
		fmt.Printf("Error: %v\n", err)
		return
	}
}

func update_function() {
	for key, _ := range aicore_component_info {
		// fmt.Printf("%s value is %v\n", key, value)
		for _, element := range imagelist.Images.Used {
			splitting_image_name := strings.Split(element.Image, "/")
			temp_comp_name := splitting_image_name[len(splitting_image_name)-1]
			if key == temp_comp_name {
				fmt.Printf("Element: %q, Tag:%q\n", temp_comp_name, element.Tag)
			}
		}
	}
}

func main() {
	current_path := aicorefolder_path
	fmt.Println("Gathering information for aicore folder")
	gather_aicore_info(current_path)
	// for key, value := range aicore_component_info {
	// 	fmt.Printf("%s value is %v\n", key, value)
	// }
	// aicore_component_info is available now

	fmt.Println("Gathering information from infra-tooling list")
	current_path = infrafolder_path
	gather_infra_tooling_info(current_path)
	// fmt.Printf("%+v\n", imagelist)
	// images_list info is present in imagelist

	update_function()
}
