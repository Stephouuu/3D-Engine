#include "Texture.hpp"

Texture::Texture()
{
	init();
}

Texture::Texture(const ofFbo & fbo)
{
	init();
	loadFromFbo(fbo);
}

Texture::Texture(const std::string & path)
{
	init();
	loadFromImage(path);
}

void Texture::init(void)
{
	selectedComposition_ = CompositionType::NONE;
	selectedFilter_ = FilterType::NONE_FILTER;
	image_ = nullptr;
	composition_ = nullptr;

	kernels_[FilterType::BLUR] = { { 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f },
	{ 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f },
	{ 1.0f / 9.0f, 1.0f / 9.0f, 1.0f / 9.0f } };

	kernels_[FilterType::EDGE_DETECT] = { { -1.0f, -1.0f, -1.0f },
	{ -1.0f, 8.0f, -1.0f },
	{ -1.0f, -1.0f, -1.0f } };

	kernels_[FilterType::EMBROSS] = { { -2.0f, -1.0f, 0.0f },
	{ -1.0f, 1.0f, 1.0f },
	{ 0.0f, 1.0f, 2.0f } };

	kernels_[FilterType::SHARPEN] = { { 0.0f, -1.0f, 0.0f },
	{ -1.0f, 5.0f, -1.0f },
	{ 0.0f, -1.0f, 0.0f } };

	kernels_[FilterType::EDGE_ENFORCED] = { { 0.0f, 0.0f, 0.0f },
	{ -1.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f } };

	kernels_[FilterType::UNSHARP_MASKING] = { { -1.0f / 256, -4.0f / 256, -6.0f / 256, -4.0f / 256, -1.0f / 256 },
	{ -4.0f / 256, -16.0f / 256, -24.0f / 256, -16.0f / 256, -4.0f / 256 },
	{ -6.0f / 256, -24.0f / 256, 476.0f / 256, -24.0f / 256, -6.0f / 256 },
	{ -4.0f / 256, -16.0f / 256, -24.0f / 256, -16.0f / 256, -4.0f / 256 },
	{ -1.0f / 256, -4.0f / 256, -6.0f / 256, -4.0f / 256, -1.0f / 256 } };

	labelKernel_["Flou gaussien"] = FilterType::BLUR;
	labelKernel_["Detection de bordure"] = FilterType::EDGE_DETECT;
	labelKernel_["Relief"] = FilterType::EMBROSS;
	labelKernel_["Affiner"] = FilterType::SHARPEN;
	labelKernel_["Bordure renforcé"] = FilterType::EDGE_ENFORCED;
	labelKernel_["Masque de flou"] = FilterType::UNSHARP_MASKING;
}

void Texture::loadImage(const ofImage *image)
{
	image_ = const_cast<ofImage *>(image);
	applyModifier();
}

void Texture::loadFromFbo(const ofFbo & fbo)
{
	texture_ = fbo.getTextureReference();
}

void Texture::loadFromImage(const std::string & path)
{
	ofImage img(path);
	texture_ = img.getTextureReference();
}

ofTexture &Texture::getTexture()
{
	return texture_;
}

void Texture::addComposition(const ofImage *image, CompositionType mode) {
	composition_ = const_cast<ofImage *>(image);
	selectedComposition_ = mode;
	applyModifier();
}

void Texture::applyModifier() {
	if (selectedComposition_ == CompositionType::NONE && selectedFilter_ == FilterType::NONE_FILTER) {
		texture_ = image_->getTexture();
	}
	else {
		compose();
		filter();
		texture_ = render_.getTexture();
	}
}


void Texture::compose() {

	if (image_ == nullptr) {
		render_ = ofImage();
		render_.allocate(100, 100, OF_IMAGE_COLOR);
		return;
	} else if (selectedComposition_ == CompositionType::NONE || composition_ == nullptr) {
		render_.clone(*image_);
		return;
	}

	ofImage draft;
	draft.allocate(static_cast<int>(image_->getWidth()), static_cast<int>(image_->getHeight()), OF_IMAGE_COLOR);

	unsigned int i = 0;
	while (i < image_->getPixels().size() && i < composition_->getPixels().size()) {
		switch (selectedComposition_) {
		case AVG:
			draft.setColor(i, (image_->getColor(i) + composition_->getColor(i)) / 2);
			break;
		case ADD:
			draft.setColor(i, (image_->getColor(i) + composition_->getColor(i)));
			break;
		case SUB:
			draft.setColor(i, (image_->getColor(i) - composition_->getColor(i)));
			break;
		case MUL:
			draft.setColor(i, (image_->getColor(i) * composition_->getColor(i)));
			break;
		case DARK:
			draft.setColor(i, (image_->getPixels()[i] < composition_->getPixels()[i] ? image_->getColor(i)
				: composition_->getColor(i)));
			break;
		case LIGHT:
			draft.setColor(i, (image_->getPixels()[i] > composition_->getPixels()[i] ? image_->getColor(i)
				: composition_->getColor(i)));
			break;
		case DIFF:
			draft.setColor(i, composition_->getColor(i) - composition_->getColor(i));
			break;
		case NONE:
			break;
		}
		i += 1;
	}
	render_.clone(draft);
}

void Texture::filter() {

	if (selectedFilter_ == FilterType::NONE_FILTER || image_ == nullptr) {
		return;
	}

	ofImage draft;
	draft.allocate(static_cast<int>(image_->getWidth()), static_cast<int>(image_->getHeight()), OF_IMAGE_COLOR);
	draft.clone(render_);

	ofPixels src = draft.getPixels();
	ofPixels dest = render_.getPixels();

	ofColor pixel_color_src;
	ofColor pixel_color_dest;

	float sum[3];
	for (int y = 0; y < draft.getHeight(); ++y) {
		for (int x = 0; x < draft.getWidth(); ++x) {
			for (int c = 0; c < 3; ++c)
				sum[c] = 0;
			for (int j = 0; j < kernel_size; ++j) {
				for (int i = 0; i < kernel_size; ++i) {
					size_t idx = static_cast<size_t>((draft.getWidth() * (y + j - kernel_offset) + (x + i - kernel_offset)) * 3);
					if (idx < src.size()){
						pixel_color_src = src.getColor(idx);
						for (int c = 0; c < 3; ++c) {
							sum[c] = sum[c] + kernels_[selectedFilter_][i][j] * pixel_color_src[c];
						}	
					}
                }
            }
            for (int c = 0; c < 3; ++c) {
                pixel_color_dest[c] = static_cast<unsigned char>((int) ofClamp(sum[c], 0, 255));
            }
            dest.setColor(static_cast<size_t>((draft.getWidth() * y + x) * 3), pixel_color_dest);
        }
    }
    render_.setFromPixels(dest);
    render_.update();
}

void Texture::setFilter(Texture::FilterType filter) {
    selectedFilter_ = filter;
    applyModifier();
}

map<string, Texture::FilterType> &Texture::getLabelFilter() {
    return labelKernel_;
}
