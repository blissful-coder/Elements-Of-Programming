package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"regexp"

	"gopkg.in/yaml.v3"
)

type PRDescriptionYAML struct {
	CommitHash   string              `yaml:"commitHash"`
	Component    string              `yaml:"component"`
	Version      string              `yaml:"version"`
	ChangeOwners []string            `yaml:"changeOwners"`
	ReleaseNotes []map[string]string `yaml:"releaseNotes"`
}

func main() {
	filename := os.Args[1]
	var info PRDescriptionYAML
	source, err := ioutil.ReadFile(filename)
	// fmt.Printf("Value: %s\n", source)
	if err != nil {
		panic(err)
	}
	re := regexp.MustCompile("(?s)(```)yaml(.*)(```)")
	yamldata := re.FindStringSubmatch(string(source))[2]
	err = yaml.Unmarshal([]byte(yamldata), &info)
	if err != nil {
		panic(err)
	}
	fmt.Printf("Value: %#v\n", info.CommitHash)
	fmt.Printf("Value: %#v\n", info.Component)
	fmt.Printf("Value: %#v\n", info.Version)
	fmt.Printf("Value: %#v\n", info.ChangeOwners)
	fmt.Printf("Value: %#v\n", info.ReleaseNotes)

	for _, element := range info.ChangeOwners {
		fmt.Printf("CodeOwner: %#v\n", element)
	}
}
